#ifndef BLOCKCHAIN_MINER_H
#define BLOCKCHAIN_MINER_H


#include <iostream>
#include <vector>
#include <thread>
#include "Transaction.h"
#include "Mempool.h"

using namespace std::chrono_literals;

class Miner {
    std::vector<Transaction>& pool;

public:
    Miner(std::vector<Transaction>& mempool);
    void run();
};


#endif