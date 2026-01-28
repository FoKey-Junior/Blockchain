#ifndef BLOCKCHAIN_MEMPOOL_H
#define BLOCKCHAIN_MEMPOOL_H

#include <deque>
#include <mutex>
#include <optional>
#include <sodium.h>
#include "Transaction.h"

class Mempool {
    static constexpr size_t MAX_MEMPOOL_SIZE = 100'000;
    std::deque<Transaction> pool_;
    mutable std::mutex mutex_;

public:
    bool add_transaction(const Transaction& transaction);
    bool remove_transaction(const unsigned char* transaction);
    std::optional<Transaction> pop_transaction();
};

#endif