#ifndef BLOCKCHAIN_STORAGE_BLOCK_STORE_H
#define BLOCKCHAIN_STORAGE_BLOCK_STORE_H

#include "storage/database.h"
#include <vector>
#include <string>

namespace storage {

struct StoredBlock {
    std::string hash;
    std::string previous_hash;
    std::int64_t timestamp_ms;
    std::string authority;
};

class BlockStore {
public:
    explicit BlockStore(Database& db);
    void add(const StoredBlock& block);
    std::vector<StoredBlock> list();

private:
    Database& db_;
};

} // namespace storage

#endif
