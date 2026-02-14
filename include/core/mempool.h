#ifndef BLOCKCHAIN_CORE_MEMPOOL_H
#define BLOCKCHAIN_CORE_MEMPOOL_H

#include "transaction.h"
#include <deque>
#include <mutex>
#include <optional>

namespace core {

class Mempool {
public:
    bool push(Transaction tx);
    std::optional<Transaction> pop();
    std::size_t size() const;
    bool empty() const;
    void clear();

private:
    std::deque<Transaction> queue_;
    mutable std::mutex mutex_;
};

} // namespace core

#endif
