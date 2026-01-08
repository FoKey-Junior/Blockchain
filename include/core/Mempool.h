#ifndef BLOCKCHAIN_MEMPOOL_H
#define BLOCKCHAIN_MEMPOOL_H


#include <vector>
#include "Transaction.h"

class Mempool {
public:
    void submit(Transaction transaction);
    bool hasTransactions() const;
    std::vector<Transaction> collect(size_t max);

private:
    std::vector<Transaction> pool;
};


#endif