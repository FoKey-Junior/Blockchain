#ifndef MEMPOOL_H
#define MEMPOOL_H

#include "transaction.h"
#include <deque>
#include <mutex>
#include <optional>
#include <cstddef>

class mempool {
private:
    static constexpr std::size_t max_size = 100'000;
    std::deque<transaction> queue_;
    mutable std::mutex mutex_;

    [[nodiscard]] bool contains_transaction(const address_bytes& address) const noexcept;

public:
    mempool() = default;
    ~mempool() = default;

    mempool(const mempool&) = delete;
    mempool& operator=(const mempool&) = delete;
    mempool(mempool&&) = delete;
    mempool& operator=(mempool&&) = delete;

    [[nodiscard]] bool add_transaction(const transaction& transaction) noexcept;
    [[nodiscard]] bool remove_transaction(const address_bytes& address) noexcept;
    [[nodiscard]] std::optional<transaction> pop_transaction() noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    void clear() noexcept;
};

#endif

