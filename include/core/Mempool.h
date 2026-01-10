#ifndef BLOCKCHAIN_MEMPOOL_H
#define BLOCKCHAIN_MEMPOOL_H

#include <unordered_map>
#include <queue>
#include <vector>
#include <array>
#include <memory>
#include <mutex>
#include <string_view>
#include "../../include/core/Transaction.h"

struct AddressHasher {
    std::size_t operator()(const std::array<unsigned char, crypto_generichash_BYTES>& address) const;
};

class Mempool {
private:
    std::unordered_map<std::array<unsigned char, crypto_generichash_BYTES>,
                       std::shared_ptr<Transaction>,
                       AddressHasher> transaction_map;

    std::queue<std::array<unsigned char, crypto_generichash_BYTES>> transaction_order;
    std::mutex mutex;

public:
    bool add_transaction(const std::shared_ptr<Transaction>& transaction);
    std::vector<std::shared_ptr<Transaction>> get_transactions_for_mining(size_t maxTransactions);
    size_t get_transaction_count();
};

#endif
