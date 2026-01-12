#include "../../include/core/Miner.h"

Miner::Miner(std::vector<Transaction>& mempool) : pool(mempool) {}

void Miner::run() {
    while (true) {
        if (!pool.empty()) {
            std::cout << "\n\n\nНе пуст\n\n\n";
        } else {
            std::cout << "\n\n\nПуст\n\n\n";

        }

        std::this_thread::sleep_for(500ms);
    }
}