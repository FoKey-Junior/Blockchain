#ifndef NODE_H
#define NODE_H

#include "../blockchain/Transaction.h"
#include "../blockchain/Blockchain.h"
#include "../blockchain/Miner.h"
#include "../blockchain/Block.h"
#include "Peer.h"
#include "Message.h"
#include "CryptoUtils.h"

#include <asio.hpp>
#include <vector>
#include <deque>
#include <mutex>
#include <memory>
#include <algorithm>

struct PeerConnection {
    Peer peer;
    std::shared_ptr<asio::ip::tcp::socket> socket;
};

class Node {
private:
    asio::io_context& io_context_;
    asio::ip::tcp::acceptor acceptor_;
    unsigned char pub_key_[crypto_sign_PUBLICKEYBYTES]{};
    unsigned char priv_key_[crypto_sign_SECRETKEYBYTES]{};

    std::vector<Transaction>* mempool = nullptr;
    Blockchain* blockchain = nullptr;
    Miner* miner = nullptr;
    std::function<void()> on_blockchain_updated = nullptr;  // Callback при обновлении блокчейна

    std::deque<std::vector<uint8_t>> mempool_;
    std::mutex mempool_mutex_;
    std::vector<PeerConnection> peers_;
    std::mutex peers_mutex_;

    // Асинхронные внутренние методы
    void accept() noexcept;
    void handle_connection(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    void read_message(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    void handle_message(MessageType type, const std::vector<uint8_t>& payload) noexcept;
    std::vector<uint8_t> serialize_message(const Message& msg) const noexcept;
    Message deserialize_message(const std::vector<uint8_t>& buf) const noexcept;

public:
    Node(asio::io_context& io, uint16_t port,
         const unsigned char* pub_key, const unsigned char* priv_key) noexcept;

    void set_mempool(std::vector<Transaction>* m) { 
        mempool = m; 
        if (miner && m) {
            miner->set_mempool_mutex(&mempool_mutex_);
        }
    }
    void set_blockchain(Blockchain* bc) { blockchain = bc; }
    void set_on_blockchain_updated(std::function<void()> callback) { on_blockchain_updated = callback; }
    void set_miner(Miner* m) { 
        miner = m; 
        if (m) {
            m->set_node(this);
            m->set_mempool_mutex(&mempool_mutex_);
        }
    }

    void start() noexcept;

    void connect_to_peer(const std::string& ip, uint16_t port) noexcept;
    void send_hello(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    void broadcast_message(const Message& msg) noexcept;
    void add_transaction(const std::vector<uint8_t>& tx) noexcept;
    void process_mempool() noexcept;

    void connect_to_server(const std::string& host, uint16_t port) noexcept;
    void broadcast_block(const Block& block) noexcept;
    void notify_tx_processed(const std::vector<Transaction>& txs) noexcept;
    std::mutex* get_mempool_mutex() { return &mempool_mutex_; }
    Blockchain* get_blockchain() { return blockchain; }
};

#endif
