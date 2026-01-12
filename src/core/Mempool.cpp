#include "../../include/core/Mempool.h"

void Mempool::add_transaction(const Transaction& transaction) {
    pool.push_back(transaction);
}

Transaction Mempool::pop_transaction() const {
    if (pool.empty()) throw std::runtime_error("Mempool is empty");
    return pool[0];
}
