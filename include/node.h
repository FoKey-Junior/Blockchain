#ifndef NODE_H
#define NODE_H

#include "message.h"
#include "transaction.h"
#include "block.h"
#include "peer.h"
#include "types.h"
#include <asio.hpp>
#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>
#include <functional>
#include <cstdint>

struct peer_connection {
    peer peer_data;
    std::shared_ptr<asio::ip::tcp::socket> socket;
};

class blockchain;
class miner;
class mempool;

class node {
private:
    asio::io_context& io_context_;
    asio::ip::tcp::acceptor acceptor_;
    public_key_bytes public_key_;
    private_key_bytes private_key_;

    blockchain* blockchain_ptr_;
    miner* miner_ptr_;
    mempool* mempool_ptr_;
    std::function<void()> on_blockchain_updated_;

    std::deque<std::vector<std::uint8_t>> transaction_queue_;
    std::mutex transaction_queue_mutex_;
    std::condition_variable transaction_queue_condition_;

    std::vector<peer_connection> peers_;
    std::mutex peers_mutex_;

    void accept_connection() noexcept;
    void handle_connection(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    void read_message(std::shared_ptr<asio::ip::tcp::socket> socket) noexcept;
    void handle_message(message_type type, const std::vector<std::uint8_t>& payload) noexcept;
    [[nodiscard]] std::vector<std::uint8_t> serialize_message(const message& msg) const noexcept;
    [[nodiscard]] message deserialize_message(const std::vector<std::uint8_t>& buffer) const noexcept;

public:
    node(asio::io_context& io_context, std::uint16_t port,
         const public_key_bytes& public_key, const private_key_bytes& private_key) noexcept;
    ~node() = default;

    node(const node&) = delete;
    node& operator=(const node&) = delete;
    node(node&&) = delete;
    node& operator=(node&&) = delete;

    void set_blockchain(blockchain* blockchain_ptr) noexcept { blockchain_ptr_ = blockchain_ptr; }
    void set_miner(miner* miner_ptr) noexcept { miner_ptr_ = miner_ptr; }
    void set_mempool(mempool* mempool_ptr) noexcept { mempool_ptr_ = mempool_ptr; }
    void set_on_blockchain_updated(std::function<void()> callback) noexcept { on_blockchain_updated_ = std::move(callback); }

    void start() noexcept;
    void connect_to_peer(const std::string& ip_address, std::uint16_t port) noexcept;
    void broadcast_message(const message& msg) noexcept;
    void add_transaction(const std::vector<std::uint8_t>& transaction_data) noexcept;
    void broadcast_block(const block& block_to_broadcast) noexcept;
    void notify_transactions_processed(const std::vector<transaction>& transactions) noexcept;
    void notify_mempool_changed() noexcept;
    void wait_for_mempool(std::unique_lock<std::mutex>& lock, std::chrono::milliseconds timeout) noexcept;
    [[nodiscard]] std::mutex* get_mempool_mutex() noexcept { return &transaction_queue_mutex_; }
    [[nodiscard]] blockchain* get_blockchain() const noexcept { return blockchain_ptr_; }
};

#endif

