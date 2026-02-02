#include "../include/mempool.h"
#include <algorithm>
#include <cstring>

bool mempool::contains_transaction(const address_bytes& address) const noexcept {
    return std::any_of(queue_.begin(), queue_.end(),
        [&address](const transaction& tx) {
            return std::memcmp(tx.get_address().data(), address.data(), address_bytes::size()) == 0;
        });
}

bool mempool::add_transaction(const transaction& transaction) noexcept {
    std::scoped_lock lock(mutex_);

    if (queue_.size() >= max_size) {
        return false;
    }

    if (contains_transaction(transaction.get_address())) {
        return false;
    }

    queue_.push_back(transaction);
    return true;
}

bool mempool::remove_transaction(const address_bytes& address) noexcept {
    std::scoped_lock lock(mutex_);

    const auto it = std::find_if(queue_.begin(), queue_.end(),
        [&address](const transaction& tx) {
            return std::memcmp(tx.get_address().data(), address.data(), address_bytes::size()) == 0;
        });

    if (it == queue_.end()) {
        return false;
    }

    queue_.erase(it);
    return true;
}

std::optional<transaction> mempool::pop_transaction() noexcept {
    std::scoped_lock lock(mutex_);

    if (queue_.empty()) {
        return std::nullopt;
    }

    transaction tx = std::move(queue_.front());
    queue_.pop_front();
    return tx;
}

std::size_t mempool::size() const noexcept {
    std::scoped_lock lock(mutex_);
    return queue_.size();
}

bool mempool::empty() const noexcept {
    std::scoped_lock lock(mutex_);
    return queue_.empty();
}

void mempool::clear() noexcept {
    std::scoped_lock lock(mutex_);
    queue_.clear();
}

