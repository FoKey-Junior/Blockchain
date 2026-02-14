#include "core/user.h"

namespace core {

User::User(std::string name, KeyPair keys)
    : name_(std::move(name)), keys_(std::move(keys)) {}

AddressBytes User::address() const noexcept {
    std::vector<std::uint8_t> data(keys_.public_key.begin(), keys_.public_key.end());
    return crypto::blake2b_256(data);
}

} // namespace core
