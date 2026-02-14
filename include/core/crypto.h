#ifndef BLOCKCHAIN_CORE_CRYPTO_H
#define BLOCKCHAIN_CORE_CRYPTO_H

#include "types.h"
#include <string>
#include <vector>

namespace core::crypto {

bool init() noexcept;

struct KeyPair {
    PublicKeyBytes public_key;
    PrivateKeyBytes private_key;
};

KeyPair generate_keypair() noexcept;

HashBytes sha256(const std::vector<std::uint8_t>& data) noexcept;
HashBytes sha256_file(const std::string& path, bool& ok) noexcept;

AddressBytes blake2b_256(const std::vector<std::uint8_t>& data) noexcept;

SignatureBytes sign(const std::vector<std::uint8_t>& data, const PrivateKeyBytes& private_key) noexcept;
bool verify(const std::vector<std::uint8_t>& data, const SignatureBytes& signature,
            const PublicKeyBytes& public_key) noexcept;

std::string to_hex(const std::uint8_t* data, std::size_t size);
std::string to_hex(const std::vector<std::uint8_t>& data);
template <std::size_t N>
std::string to_hex(const std::array<std::uint8_t, N>& data) {
    return to_hex(data.data(), data.size());
}

std::vector<std::uint8_t> from_hex(const std::string& hex);
AddressBytes address_from_hex(const std::string& hex);
HashBytes hash_from_hex(const std::string& hex);

} // namespace core::crypto

#endif
