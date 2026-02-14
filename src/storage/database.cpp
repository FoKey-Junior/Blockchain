#include "storage/database.h"

#include <stdexcept>

namespace storage {

Database::Database(std::string path)
    : path_(std::move(path)) {
    if (sqlite3_open(path_.c_str(), &db_) != SQLITE_OK) {
        throw std::runtime_error("Failed to open database");
    }
}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
    }
}

void Database::execute(const std::string& sql) {
    char* err_msg = nullptr;
    if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK) {
        std::string msg = err_msg ? err_msg : "SQL error";
        sqlite3_free(err_msg);
        throw std::runtime_error(msg);
    }
}

void Database::init_schema() {
    execute(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "address TEXT NOT NULL UNIQUE,"
        "public_key BLOB NOT NULL,"
        "private_key BLOB NOT NULL,"
        "host TEXT NOT NULL,"
        "port INTEGER NOT NULL);"
    );

    execute(
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "tx_id TEXT NOT NULL,"
        "sender TEXT NOT NULL,"
        "receiver TEXT NOT NULL,"
        "file_hash TEXT NOT NULL,"
        "file_name TEXT NOT NULL,"
        "file_size INTEGER NOT NULL,"
        "mime TEXT NOT NULL,"
        "block_index INTEGER NOT NULL,"
        "timestamp INTEGER NOT NULL);"
    );

    execute(
        "CREATE TABLE IF NOT EXISTS blocks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "hash TEXT NOT NULL,"
        "previous_hash TEXT NOT NULL,"
        "timestamp INTEGER NOT NULL,"
        "authority TEXT NOT NULL);"
    );
}

} // namespace storage
