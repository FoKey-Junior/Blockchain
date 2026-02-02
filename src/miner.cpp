#include "../include/miner.h"
#include "../include/node.h"
#include <vector>
#include <chrono>
#include <thread>

miner::miner(mempool& mempool_ref) noexcept
    : mempool_ref_(mempool_ref),
      blockchain_ptr_(nullptr),
      node_ptr_(nullptr),
      running_(false) {
}

miner::~miner() noexcept {
    stop();
}

void miner::mining_loop() noexcept {
    while (running_.load()) {
        std::vector<transaction> transactions;

        {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait_for(lock, std::chrono::milliseconds(200),
                [this] { return !mempool_ref_.empty() || !running_.load(); });

            if (!running_.load()) {
                break;
            }

            constexpr std::size_t max_transactions_per_block = 100;
            for (std::size_t i = 0; i < max_transactions_per_block && !mempool_ref_.empty(); ++i) {
                auto tx_opt = mempool_ref_.pop_transaction();
                if (tx_opt.has_value()) {
                    transactions.push_back(std::move(tx_opt.value()));
                }
            }
        }

        if (!transactions.empty() && blockchain_ptr_) {
            blockchain_ptr_->add_block(transactions);
            const block& new_block = blockchain_ptr_->get_last_block();

            if (node_ptr_) {
                node_ptr_->broadcast_block(new_block);
                node_ptr_->notify_transactions_processed(transactions);
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}

void miner::start() noexcept {
    if (running_.exchange(true)) {
        return;
    }

    mining_thread_ = std::thread(&miner::mining_loop, this);
}

void miner::stop() noexcept {
    if (!running_.exchange(false)) {
        return;
    }

    condition_.notify_all();

    if (mining_thread_.joinable()) {
        mining_thread_.join();
    }
}

