#include "../../include/core/Mempool.h"

std::size_t AddressHasher::operator()(const std::array<unsigned char, crypto_generichash_BYTES>& address) const {
    return std::hash<std::string_view>{}(
        std::string_view(reinterpret_cast<const char*>(address.data()), address.size())
    );
}

bool Mempool::add_transaction(const std::shared_ptr<Transaction>& transaction) {
    std::lock_guard<std::mutex> lock(mutex);

    std::array<unsigned char, crypto_generichash_BYTES> transaction_address = transaction->get_address_array();

    if (transaction_map.find(transaction_address) != transaction_map.end()) {
        return false;
    }

    transaction_map[transaction_address] = transaction;
    transaction_order.push(transaction_address);

    return true;
}

std::vector<std::shared_ptr<Transaction>> Mempool::get_transactions_for_mining(size_t maxTransactions) {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::shared_ptr<Transaction>> transactions_to_mine;

    while (!transaction_order.empty() && transactions_to_mine.size() < maxTransactions) {
        std::array<unsigned char, crypto_generichash_BYTES> transaction_address = transaction_order.front();
        transaction_order.pop();

        auto iterator = transaction_map.find(transaction_address);
        if (iterator != transaction_map.end()) {
            transactions_to_mine.push_back(iterator->second);
            transaction_map.erase(iterator);
        }
    }

    return transactions_to_mine;
}

size_t Mempool::get_transaction_count() {
    std::lock_guard<std::mutex> lock(mutex);
    return transaction_map.size();
}
