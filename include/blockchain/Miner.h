#ifndef MINER_H
#define MINER_H

#include "Transaction.h"
#include "Blockchain.h"
#include <vector>
#include <mutex>

class Miner {
private:
    std::vector<Transaction>& mempool;
    std::mutex mempool_mutex;
    Blockchain* blockchain = nullptr;

public:
    explicit Miner(std::vector<Transaction>& mempool_);

    // Сеттер для блокчейна
    void set_blockchain(Blockchain* bc) { blockchain = bc; }

    // Запуск майнинга
    void start_mining();
};

#endif
