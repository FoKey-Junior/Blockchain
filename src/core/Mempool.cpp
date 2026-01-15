#include "../../include/core/Mempool.h"
#include <ranges>
#include <algorithm>
#include <cstring>

bool Mempool::add_transaction(const Transaction& transaction) {
    std::scoped_lock lock(mutex_);

    if (std::ranges::any_of(pool_, [&transaction](const Transaction& current_transaction) {
        return std::memcmp(
            current_transaction.get_address_bytes(),
            transaction.get_address_bytes(),
            crypto_generichash_BYTES) == 0;
        }) || pool_.size() >= MAX_MEMPOOL_SIZE) {

        return false;
        }

    pool_.push_back(transaction);
    return true;
}

bool Mempool::remove_transaction(const unsigned char* address_bytes) {
    std::scoped_lock lock(mutex_);

    auto it = std::ranges::find_if(pool_, [&](const Transaction& tx) {
        return std::memcmp(
            tx.get_address_bytes(),
            address_bytes,
            crypto_generichash_BYTES
        ) == 0;
    });

    if (it == pool_.end()) {
        return false;
    }

    pool_.erase(it);
    return true;
}

std::optional<Transaction> Mempool::pop_transaction() {
    std::scoped_lock lock(mutex_);

    if (pool_.empty()) {
        return std::nullopt;
    } else {
        Transaction transaction = pool_.front();
        pool_.pop_front();
        return transaction;
    }
}

