#include "storage/tx_store.h"

#include <sqlite3.h>
#include <stdexcept>

namespace storage {

TxStore::TxStore(Database& db) : db_(db) {}

void TxStore::add(const StoredTransaction& tx) {
    const char* sql =
        "INSERT INTO transactions "
        "(tx_id, sender, receiver, file_hash, file_name, file_size, mime, block_index, timestamp) "
        "VALUES (?,?,?,?,?,?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare tx add");
    }
    sqlite3_bind_text(stmt, 1, tx.tx_id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, tx.sender.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, tx.receiver.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, tx.file_hash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, tx.file_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 6, static_cast<sqlite3_int64>(tx.file_size));
    sqlite3_bind_text(stmt, 7, tx.mime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 8, tx.block_index);
    sqlite3_bind_int64(stmt, 9, tx.timestamp_ms);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute tx add");
    }
    sqlite3_finalize(stmt);
}

std::vector<StoredTransaction> TxStore::list() {
    const char* sql =
        "SELECT tx_id, sender, receiver, file_hash, file_name, file_size, mime, block_index, timestamp "
        "FROM transactions ORDER BY id DESC;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare tx list");
    }
    std::vector<StoredTransaction> out;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        StoredTransaction tx;
        tx.tx_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        tx.sender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        tx.receiver = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        tx.file_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        tx.file_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        tx.file_size = static_cast<std::uint64_t>(sqlite3_column_int64(stmt, 5));
        tx.mime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        tx.block_index = sqlite3_column_int64(stmt, 7);
        tx.timestamp_ms = sqlite3_column_int64(stmt, 8);
        out.push_back(tx);
    }
    sqlite3_finalize(stmt);
    return out;
}

std::vector<StoredTransaction> TxStore::find_by_hash(const std::string& hash) {
    const char* sql =
        "SELECT tx_id, sender, receiver, file_hash, file_name, file_size, mime, block_index, timestamp "
        "FROM transactions WHERE file_hash = ? ORDER BY id DESC;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare tx find");
    }
    sqlite3_bind_text(stmt, 1, hash.c_str(), -1, SQLITE_TRANSIENT);
    std::vector<StoredTransaction> out;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        StoredTransaction tx;
        tx.tx_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        tx.sender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        tx.receiver = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        tx.file_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        tx.file_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        tx.file_size = static_cast<std::uint64_t>(sqlite3_column_int64(stmt, 5));
        tx.mime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        tx.block_index = sqlite3_column_int64(stmt, 7);
        tx.timestamp_ms = sqlite3_column_int64(stmt, 8);
        out.push_back(tx);
    }
    sqlite3_finalize(stmt);
    return out;
}

} // namespace storage
