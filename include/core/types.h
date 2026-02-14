#ifndef BLOCKCHAIN_CORE_TYPES_H
#define BLOCKCHAIN_CORE_TYPES_H

#include <array>
#include <cstdint>
#include <string>

namespace core {

constexpr std::size_t AddressSize = 32; // BLAKE2b-256
constexpr std::size_t HashSize = 32;    // SHA-256
constexpr std::size_t SignatureSize = 64; // Ed25519
constexpr std::size_t PublicKeySize = 32;
constexpr std::size_t PrivateKeySize = 64;

using AddressBytes = std::array<std::uint8_t, AddressSize>;
using HashBytes = std::array<std::uint8_t, HashSize>;
using SignatureBytes = std::array<std::uint8_t, SignatureSize>;
using PublicKeyBytes = std::array<std::uint8_t, PublicKeySize>;
using PrivateKeyBytes = std::array<std::uint8_t, PrivateKeySize>;

struct FileMetadata {
    std::string name;
    std::uint64_t size = 0;
    std::string mime;
};

} // namespace core

#endif
