#include "core/mempool.h"

namespace core {

bool Mempool::push(Transaction tx) {
    std::scoped_lock lock(mutex_);
    queue_.push_back(std::move(tx));
    return true;
}

std::optional<Transaction> Mempool::pop() {
    std::scoped_lock lock(mutex_);
    if (queue_.empty()) {
        return std::nullopt;
    }
    Transaction tx = std::move(queue_.front());
    queue_.pop_front();
    return tx;
}

std::size_t Mempool::size() const {
    std::scoped_lock lock(mutex_);
    return queue_.size();
}

bool Mempool::empty() const {
    std::scoped_lock lock(mutex_);
    return queue_.empty();
}

void Mempool::clear() {
    std::scoped_lock lock(mutex_);
    queue_.clear();
}

} // namespace core
