#ifndef NODE_H
#define NODE_H

#include "../blockchain/Transaction.h"
#include "../blockchain/Blockchain.h"
#include "../blockchain/Miner.h"
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

    std::deque<std::vector<uint8_t>> mempool_;
    std::mutex mempool_mutex_;
    std::vector<PeerConnection> peers_;
    std::mutex peers_mutex_;

    // Асинхронные внутренние методы
    void accept() noexcept;
    void handle_connection(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    void read_message(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    std::vector<uint8_t> serialize_message(const Message& msg) const noexcept;
    Message deserialize_message(const std::vector<uint8_t>& buf) const noexcept;

public:
    Node(asio::io_context& io, uint16_t port,
         const unsigned char* pub_key, const unsigned char* priv_key) noexcept;

    void set_mempool(std::vector<Transaction>* m) { mempool = m; }
    void set_blockchain(Blockchain* bc) { blockchain = bc; }
    void set_miner(Miner* m) { miner = m; }

    void start() noexcept;

    void connect_to_peer(const std::string& ip, uint16_t port) noexcept;
    void broadcast_message(const Message& msg) noexcept;
    void add_transaction(const std::vector<uint8_t>& tx) noexcept;
    void process_mempool() noexcept;
};

#endif
