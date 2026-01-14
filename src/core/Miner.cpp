#include "../../include/core/Miner.h"

Miner::Miner(std::vector<Transaction>& mempool) : pool(mempool) {}

void Miner::run() {
    int score = 0;

    while (true) {
        score++;

        if (!pool.empty()) {
            std::cout << score << ". Не пуст\n";
        } else {
            std::cout << score << ". Пуст\n";

        }

        std::this_thread::sleep_for(500ms);
    }
}