#ifndef BLOCKCHAIN_CORE_USER_H
#define BLOCKCHAIN_CORE_USER_H

#include "types.h"
#include "crypto.h"
#include <string>

namespace core {

using crypto::KeyPair;

class User {
public:
    User(std::string name, KeyPair keys);

    const std::string& name() const noexcept { return name_; }
    const PublicKeyBytes& public_key() const noexcept { return keys_.public_key; }
    const PrivateKeyBytes& private_key() const noexcept { return keys_.private_key; }
    AddressBytes address() const noexcept;

private:
    std::string name_;
    KeyPair keys_;
};

} // namespace core

#endif
