#include "../include/blockchain/Miner.h"
#include <thread>
#include <iostream>
#include <chrono>

Miner::Miner(std::vector<Transaction>& mempool_) : mempool(mempool_) {}

void Miner::start_mining() {
    std::thread([this]() {
        while (true) {
            std::vector<Transaction> txs;

            // безопасно копируем транзакции из мемпула
            {
                std::lock_guard<std::mutex> lock(mempool_mutex);
                if (!mempool.empty()) {
                    txs = mempool;         // копируем для обработки
                    mempool.clear();       // очищаем мемпул
                }
            }

            if (!txs.empty()) {
                std::cout << "[Miner] Mining a block with " << txs.size() << " txs...\n";

                if (blockchain) {
                    blockchain->add_block(txs); // добавляем блок в цепочку
                }

                // имитация PoW
                std::this_thread::sleep_for(std::chrono::seconds(1));
            } else {
                // если нет транзакций — ждём
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }).detach();
}
