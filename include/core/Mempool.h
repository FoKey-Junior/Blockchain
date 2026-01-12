#ifndef BLOCKCHAIN_MEMPOOL_H
#define BLOCKCHAIN_MEMPOOL_H


#include <vector>
#include "Transaction.h"

class Mempool {
public:
    std::vector<Transaction> pool;

    void add_transaction(const Transaction& transaction);
    Transaction pop_transaction() const;
};


#endif