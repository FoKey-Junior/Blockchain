#ifndef BLOCKCHAIN_STORAGE_TX_STORE_H
#define BLOCKCHAIN_STORAGE_TX_STORE_H

#include "storage/database.h"
#include "core/types.h"
#include <vector>

namespace storage {

struct StoredTransaction {
    std::string tx_id;
    std::string sender;
    std::string receiver;
    std::string file_hash;
    std::string file_name;
    std::uint64_t file_size;
    std::string mime;
    std::int64_t timestamp_ms;
    std::int64_t block_index;
};

class TxStore {
public:
    explicit TxStore(Database& db);
    void add(const StoredTransaction& tx);
    std::vector<StoredTransaction> list();
    std::vector<StoredTransaction> find_by_hash(const std::string& hash);

private:
    Database& db_;
};

} // namespace storage

#endif
