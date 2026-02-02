#ifndef MINER_H
#define MINER_H

#include "mempool.h"
#include "blockchain.h"
#include <memory>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>

class node;

class miner {
private:
    mempool& mempool_ref_;
    blockchain* blockchain_ptr_;
    node* node_ptr_;
    std::atomic<bool> running_;
    std::thread mining_thread_;
    std::mutex mutex_;
    std::condition_variable condition_;

    void mining_loop() noexcept;

public:
    explicit miner(mempool& mempool_ref) noexcept;
    ~miner() noexcept;

    miner(const miner&) = delete;
    miner& operator=(const miner&) = delete;
    miner(miner&&) = delete;
    miner& operator=(miner&&) = delete;

    void set_blockchain(blockchain* blockchain_ptr) noexcept { blockchain_ptr_ = blockchain_ptr; }
    void set_node(node* node_ptr) noexcept { node_ptr_ = node_ptr; }

    void start() noexcept;
    void stop() noexcept;
    [[nodiscard]] bool is_running() const noexcept { return running_.load(); }
};

#endif

