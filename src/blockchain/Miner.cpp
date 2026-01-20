#include "../../include/blockchain/Miner.h"
#include <thread>
#include <iostream>
#include <chrono>

Miner::Miner(std::vector<Transaction>& mempool_) : mempool(mempool_) {}

void Miner::start_mining() {
    std::thread([this]() {
        while (true) {
            std::vector<Transaction> txs;
            {
                std::lock_guard<std::mutex> lock(mempool_mutex);
                if (!mempool.empty()) {
                    txs = mempool;
                    mempool.clear();
                }
            }

            if (!txs.empty() && blockchain) {
                std::cout << "[Miner] Mining a block with " << txs.size() << " transactions...\n";
                blockchain->add_block(txs);
                std::this_thread::sleep_for(std::chrono::seconds(1)); // имитация PoW
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }).detach();
}
