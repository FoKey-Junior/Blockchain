#include "storage/block_store.h"

#include <sqlite3.h>
#include <stdexcept>
#include <cstdint>

namespace storage {

BlockStore::BlockStore(Database& db) : db_(db) {}

void BlockStore::add(const StoredBlock& block) {
    const char* sql =
        "INSERT INTO blocks (hash, previous_hash, timestamp, authority) VALUES (?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare block add");
    }
    sqlite3_bind_text(stmt, 1, block.hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, block.previous_hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 3, block.timestamp_ms);
    sqlite3_bind_text(stmt, 4, block.authority.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute block add");
    }
    sqlite3_finalize(stmt);
}

std::vector<StoredBlock> BlockStore::list() {
    const char* sql = "SELECT hash, previous_hash, timestamp, authority FROM blocks ORDER BY id DESC;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare block list");
    }
    std::vector<StoredBlock> out;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        StoredBlock block;
        block.hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        block.previous_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        block.timestamp_ms = sqlite3_column_int64(stmt, 2);
        block.authority = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        out.push_back(block);
    }
    sqlite3_finalize(stmt);
    return out;
}

} // namespace storage
