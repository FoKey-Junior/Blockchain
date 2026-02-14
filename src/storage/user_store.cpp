#include "storage/user_store.h"

#include <sqlite3.h>
#include <stdexcept>
#include <cstring>

namespace storage {

UserStore::UserStore(Database& db) : db_(db) {}

void UserStore::add_user(const StoredUser& user) {
    const char* sql = "INSERT INTO users (name, address, public_key, private_key, host, port) VALUES (?,?,?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare add_user");
    }
    sqlite3_bind_text(stmt, 1, user.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.address_hex.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 3, user.public_key.data(), static_cast<int>(user.public_key.size()), SQLITE_TRANSIENT);
    sqlite3_bind_blob(stmt, 4, user.private_key.data(), static_cast<int>(user.private_key.size()), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, user.host.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, user.port);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to execute add_user");
    }
    sqlite3_finalize(stmt);
}

std::vector<StoredUser> UserStore::list_users() {
    const char* sql = "SELECT name, address, public_key, private_key, host, port FROM users ORDER BY name ASC;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare list_users");
    }

    std::vector<StoredUser> users;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        StoredUser user;
        user.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        user.address_hex = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const auto* pub = sqlite3_column_blob(stmt, 2);
        const auto* priv = sqlite3_column_blob(stmt, 3);
        std::memcpy(user.public_key.data(), pub, user.public_key.size());
        std::memcpy(user.private_key.data(), priv, user.private_key.size());
        user.host = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        user.port = static_cast<std::uint16_t>(sqlite3_column_int(stmt, 5));
        users.push_back(user);
    }
    sqlite3_finalize(stmt);
    return users;
}

std::vector<StoredUser> UserStore::find_by_address(const std::string& address_hex) {
    const char* sql = "SELECT name, address, public_key, private_key, host, port FROM users WHERE address = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_.handle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare find_by_address");
    }
    sqlite3_bind_text(stmt, 1, address_hex.c_str(), -1, SQLITE_TRANSIENT);
    std::vector<StoredUser> users;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        StoredUser user;
        user.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        user.address_hex = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const auto* pub = sqlite3_column_blob(stmt, 2);
        const auto* priv = sqlite3_column_blob(stmt, 3);
        std::memcpy(user.public_key.data(), pub, user.public_key.size());
        std::memcpy(user.private_key.data(), priv, user.private_key.size());
        user.host = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        user.port = static_cast<std::uint16_t>(sqlite3_column_int(stmt, 5));
        users.push_back(user);
    }
    sqlite3_finalize(stmt);
    return users;
}

} // namespace storage
