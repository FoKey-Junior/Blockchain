#include "../../include/network/Node.h"
#include <iostream>
#include <cstring>

Node::Node(asio::io_context& io, uint16_t port,
           const unsigned char* pub_key, const unsigned char* priv_key) noexcept
    : io_context_(io),
      acceptor_(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    std::memcpy(pub_key_, pub_key, crypto_sign_PUBLICKEYBYTES);
    std::memcpy(priv_key_, priv_key, crypto_sign_SECRETKEYBYTES);
}

void Node::start() noexcept {
    accept();
}

// Асинхронный accept
void Node::accept() noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](auto ec) {
        if (!ec) handle_connection(socket);
        accept();
    });
}

// Обработка соединения
void Node::handle_connection(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept {
    read_message(socket);
}

// Чтение сообщений
void Node::read_message(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept {
    auto buf = std::make_shared<std::vector<uint8_t>>(2048);
    socket->async_read_some(asio::buffer(*buf), [this, buf, socket](auto ec, std::size_t length) {
        if (!ec && length > 0) {
            buf->resize(length);
            Message msg = deserialize_message(*buf);

            std::vector<uint8_t> unsigned_payload;
            if (CryptoUtils::verify_message(msg.payload, msg.sender_pub_key.data(), unsigned_payload)) {
                if (!unsigned_payload.empty()) {
                    std::lock_guard<std::mutex> lock(mempool_mutex_);
                    mempool_.push_back(unsigned_payload);
                    process_mempool();
                }
            }

            read_message(socket);
        } else if (ec) {
            std::lock_guard<std::mutex> lock(peers_mutex_);
            peers_.erase(std::remove_if(peers_.begin(), peers_.end(),
                                        [socket](const PeerConnection& pc){ return pc.socket == socket; }),
                         peers_.end());
        }
    });
}

// Подключение к пиру
void Node::connect_to_peer(const std::string& ip, uint16_t port) noexcept {
    auto socket = std::make_shared<asio::ip::tcp::socket>(io_context_);
    asio::ip::tcp::endpoint ep(asio::ip::make_address(ip), port);
    socket->async_connect(ep, [this, socket, ip, port](auto ec){
        if (!ec) {
            Peer peer(ip, port, pub_key_);
            std::lock_guard<std::mutex> lock(peers_mutex_);
            peers_.push_back(PeerConnection{peer, socket});
            handle_connection(socket);
        }
    });
}

// Рассылка
void Node::broadcast_message(const Message& msg) noexcept {
    std::vector<uint8_t> full_msg = serialize_message(msg);
    std::lock_guard<std::mutex> lock(peers_mutex_);

    for (auto it = peers_.begin(); it != peers_.end();) {
        auto& pc = *it;
        auto socket = pc.socket;
        asio::async_write(*socket, asio::buffer(full_msg),
                          [this, socket, &it](auto ec, std::size_t){
                              if (ec) {
                                  std::lock_guard<std::mutex> lock(peers_mutex_);
                                  it = peers_.erase(it);
                              }
                          });
        ++it;
    }
}

// Добавление транзакции
void Node::add_transaction(const std::vector<uint8_t>& tx) noexcept {
    std::lock_guard<std::mutex> lock(mempool_mutex_);
    mempool_.push_back(tx);
    process_mempool();
}

// Обработка мемпула
void Node::process_mempool() noexcept {
    while (!mempool_.empty()) {
        auto tx = mempool_.front();
        mempool_.erase(mempool_.begin());

        Message msg;
        msg.type = MessageType::NEW_TX;
        std::memcpy(msg.sender_pub_key.data(), pub_key_, crypto_sign_PUBLICKEYBYTES);
        msg.payload = CryptoUtils::sign_message(tx, priv_key_);

        broadcast_message(msg);
    }
}

// Сериализация
std::vector<uint8_t> Node::serialize_message(const Message& msg) const noexcept {
    std::vector<uint8_t> buf;
    buf.insert(buf.end(), msg.sender_pub_key.begin(), msg.sender_pub_key.end());
    buf.insert(buf.end(), msg.payload.begin(), msg.payload.end());
    return buf;
}

// Десериализация
Message Node::deserialize_message(const std::vector<uint8_t>& buf) const noexcept {
    Message msg;
    if (buf.size() >= crypto_sign_PUBLICKEYBYTES) {
        std::memcpy(msg.sender_pub_key.data(), buf.data(), crypto_sign_PUBLICKEYBYTES);
        msg.payload.assign(buf.begin() + crypto_sign_PUBLICKEYBYTES, buf.end());
    }
    return msg;
}
