#ifndef BLOCKCHAIN_STORAGE_USER_STORE_H
#define BLOCKCHAIN_STORAGE_USER_STORE_H

#include "storage/database.h"
#include "core/types.h"
#include <string>
#include <vector>

namespace storage {

struct StoredUser {
    std::string name;
    std::string address_hex;
    core::PublicKeyBytes public_key;
    core::PrivateKeyBytes private_key;
    std::string host;
    std::uint16_t port;
};

class UserStore {
public:
    explicit UserStore(Database& db);

    void add_user(const StoredUser& user);
    std::vector<StoredUser> list_users();
    std::vector<StoredUser> find_by_address(const std::string& address_hex);

private:
    Database& db_;
};

} // namespace storage

#endif
