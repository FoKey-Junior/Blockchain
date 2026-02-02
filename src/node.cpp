#include "../include/node.h"
#include "../include/blockchain.h"
#include "../include/miner.h"
#include "../include/mempool.h"
#include "../include/crypto_utils.h"
#include <sodium.h>
#include <iostream>
#include <cstring>
#include <algorithm>

node::node(asio::io_context& io_context, std::uint16_t port,
           const public_key_bytes& public_key, const private_key_bytes& private_key) noexcept
    : io_context_(io_context),
      acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
      public_key_(public_key),
      private_key_(private_key),
      blockchain_ptr_(nullptr),
      miner_ptr_(nullptr),
      mempool_ptr_(nullptr) {
}

void node::start() noexcept {
    accept_connection();
}

void node::accept_connection() noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](const std::error_code& ec) {
        if (!ec) {
            peer new_peer(socket->remote_endpoint().address().to_string(),
                         socket->remote_endpoint().port(), public_key_);
            {
                std::lock_guard<std::mutex> lock(peers_mutex_);
                peers_.push_back(peer_connection{new_peer, socket});
            }
            handle_connection(socket);
        }
        accept_connection();
    });
}

void node::handle_connection(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept {
    read_message(socket);
}

void node::read_message(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept {
    auto buffer = std::make_shared<std::vector<std::uint8_t>>(8192);
    socket->async_read_some(asio::buffer(*buffer), [this, buffer, socket](const std::error_code& ec, std::size_t length) {
        if (!ec && length > 0) {
            buffer->resize(length);
            const message msg = deserialize_message(*buffer);

            std::vector<std::uint8_t> unsigned_payload;
            if (crypto_utils::verify_message(msg.payload, msg.sender_public_key, unsigned_payload)) {
                if (!unsigned_payload.empty()) {
                    handle_message(msg.type, unsigned_payload);
                }
            }

            read_message(socket);
        } else if (ec) {
            std::lock_guard<std::mutex> lock(peers_mutex_);
            peers_.erase(std::remove_if(peers_.begin(), peers_.end(),
                                        [socket](const peer_connection& pc) { return pc.socket == socket; }),
                         peers_.end());
        }
    });
}

void node::handle_message(message_type type, const std::vector<std::uint8_t>& payload) noexcept {
    switch (type) {
        case message_type::new_transaction: {
            auto tx_opt = transaction::deserialize(payload);
            if (tx_opt.has_value() && mempool_ptr_) {
                if (mempool_ptr_->add_transaction(tx_opt.value())) {
                    notify_mempool_changed();
                }
            }
            break;
        }
        case message_type::new_block: {
            auto block_opt = block::deserialize(payload);
            if (block_opt.has_value() && blockchain_ptr_) {
                const block& new_block = block_opt.value();

                if (!blockchain_ptr_->empty()) {
                    const address_bytes& prev_address = blockchain_ptr_->get_last_block().get_previous_address();
                    const address_bytes& received_prev_address = new_block.get_previous_address();

                    if (std::memcmp(prev_address.data(), received_prev_address.data(), crypto_generichash_BYTES) != 0) {
                        break;
                    }
                }

                blockchain_ptr_->add_block_direct(new_block);

                if (on_blockchain_updated_) {
                    on_blockchain_updated_();
                }
            }
            break;
        }
        case message_type::transaction_processed:
        case message_type::hello:
        case message_type::ping:
        case message_type::pong:
        case message_type::peer_list:
            break;
    }
}

void node::connect_to_peer(const std::string& ip_address, std::uint16_t port) noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ip_address), port);
    socket->async_connect(endpoint, [this, socket, ip_address, port](const std::error_code& ec) {
        if (!ec) {
            peer new_peer(ip_address, port, public_key_);
            {
                std::lock_guard<std::mutex> lock(peers_mutex_);
                peers_.push_back(peer_connection{new_peer, socket});
            }
            handle_connection(socket);
        }
    });
}

void node::broadcast_message(const message& msg) noexcept {
    const std::vector<std::uint8_t> full_message = serialize_message(msg);
    
    std::vector<peer_connection> peers_copy;
    {
        std::lock_guard<std::mutex> lock(peers_mutex_);
        peers_copy = peers_;
    }

    for (auto it = peers_copy.begin(); it != peers_copy.end(); ++it) {
        auto socket = it->socket;
        asio::async_write(*socket, asio::buffer(full_message),
                         [this, socket](const std::error_code& ec, std::size_t) {
                             if (ec) {
                                 std::lock_guard<std::mutex> lock(peers_mutex_);
                                 peers_.erase(std::remove_if(peers_.begin(), peers_.end(),
                                                             [socket](const peer_connection& pc) {
                                                                 return pc.socket == socket;
                                                             }),
                                              peers_.end());
                             }
                         });
    }
}

void node::add_transaction(const std::vector<std::uint8_t>& transaction_data) noexcept {
    auto tx_opt = transaction::deserialize(transaction_data);
    if (tx_opt.has_value() && mempool_ptr_) {
        if (mempool_ptr_->add_transaction(tx_opt.value())) {
            notify_mempool_changed();

            message msg;
            msg.type = message_type::new_transaction;
            msg.sender_public_key = public_key_;
            msg.payload = crypto_utils::sign_message(transaction_data, private_key_);
            broadcast_message(msg);
        }
    }
}

void node::broadcast_block(const block& block_to_broadcast) noexcept {
    const std::vector<std::uint8_t> block_data = block_to_broadcast.serialize();

    message msg;
    msg.type = message_type::new_block;
    msg.sender_public_key = public_key_;
    msg.payload = crypto_utils::sign_message(block_data, private_key_);

    broadcast_message(msg);
}

void node::notify_transactions_processed(const std::vector<transaction>& transactions) noexcept {
    if (transactions.empty()) {
        return;
    }

    for (const auto& tx : transactions) {
        std::vector<std::uint8_t> tx_data;
        const address_bytes& tx_address = tx.get_address();
        tx_data.insert(tx_data.end(), tx_address.begin(), tx_address.end());

        message msg;
        msg.type = message_type::transaction_processed;
        msg.sender_public_key = public_key_;
        msg.payload = crypto_utils::sign_message(tx_data, private_key_);

        broadcast_message(msg);
    }
}

void node::notify_mempool_changed() noexcept {
    transaction_queue_condition_.notify_one();
}

void node::wait_for_mempool(std::unique_lock<std::mutex>& lock, std::chrono::milliseconds timeout) noexcept {
    transaction_queue_condition_.wait_for(lock, timeout);
}

std::vector<std::uint8_t> node::serialize_message(const message& msg) const noexcept {
    std::vector<std::uint8_t> buffer;
    buffer.reserve(1 + crypto_sign_PUBLICKEYBYTES + msg.payload.size());
    buffer.push_back(static_cast<std::uint8_t>(msg.type));
    buffer.insert(buffer.end(), msg.sender_public_key.begin(), msg.sender_public_key.end());
    buffer.insert(buffer.end(), msg.payload.begin(), msg.payload.end());
    return buffer;
}

message node::deserialize_message(const std::vector<std::uint8_t>& buffer) const noexcept {
    message msg;
    if (buffer.size() >= 1 + crypto_sign_PUBLICKEYBYTES) {
        msg.type = static_cast<message_type>(buffer[0]);
        std::memcpy(msg.sender_public_key.data(), buffer.data() + 1, crypto_sign_PUBLICKEYBYTES);
        msg.payload.assign(buffer.begin() + 1 + crypto_sign_PUBLICKEYBYTES, buffer.end());
    }
    return msg;
}

