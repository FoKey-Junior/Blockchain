#include "core/crypto.h"

#include <sodium.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>

namespace core::crypto {

bool init() noexcept {
    return sodium_init() >= 0;
}

KeyPair generate_keypair() noexcept {
    KeyPair pair{};
    crypto_sign_keypair(pair.public_key.data(), pair.private_key.data());
    return pair;
}

HashBytes sha256(const std::vector<std::uint8_t>& data) noexcept {
    HashBytes out{};
    crypto_hash_sha256(out.data(), data.data(), data.size());
    return out;
}

HashBytes sha256_file(const std::string& path, bool& ok) noexcept {
    HashBytes out{};
    ok = false;
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return out;
    }
    crypto_hash_sha256_state state;
    crypto_hash_sha256_init(&state);

    constexpr std::size_t buffer_size = 64 * 1024;
    std::vector<char> buffer(buffer_size);
    while (file) {
        file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const auto read_bytes = file.gcount();
        if (read_bytes > 0) {
            crypto_hash_sha256_update(&state,
                                      reinterpret_cast<const unsigned char*>(buffer.data()),
                                      static_cast<unsigned long long>(read_bytes));
        }
    }
    crypto_hash_sha256_final(&state, out.data());
    ok = true;
    return out;
}

AddressBytes blake2b_256(const std::vector<std::uint8_t>& data) noexcept {
    AddressBytes out{};
    crypto_generichash(out.data(), out.size(), data.data(), data.size(), nullptr, 0);
    return out;
}

SignatureBytes sign(const std::vector<std::uint8_t>& data, const PrivateKeyBytes& private_key) noexcept {
    SignatureBytes sig{};
    crypto_sign_detached(sig.data(), nullptr, data.data(), data.size(), private_key.data());
    return sig;
}

bool verify(const std::vector<std::uint8_t>& data, const SignatureBytes& signature,
            const PublicKeyBytes& public_key) noexcept {
    return crypto_sign_verify_detached(signature.data(), data.data(), data.size(), public_key.data()) == 0;
}

std::string to_hex(const std::uint8_t* data, std::size_t size) {
    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    for (std::size_t i = 0; i < size; ++i) {
        ss << std::setw(2) << static_cast<int>(data[i]);
    }
    return ss.str();
}

std::string to_hex(const std::vector<std::uint8_t>& data) {
    return to_hex(data.data(), data.size());
}

std::vector<std::uint8_t> from_hex(const std::string& hex) {
    std::vector<std::uint8_t> out;
    if (hex.size() % 2 != 0) {
        return out;
    }
    out.reserve(hex.size() / 2);
    for (std::size_t i = 0; i < hex.size(); i += 2) {
        auto byte = static_cast<std::uint8_t>(std::stoi(hex.substr(i, 2), nullptr, 16));
        out.push_back(byte);
    }
    return out;
}

AddressBytes address_from_hex(const std::string& hex) {
    AddressBytes out{};
    auto bytes = from_hex(hex);
    if (bytes.size() != out.size()) {
        return out;
    }
    std::memcpy(out.data(), bytes.data(), out.size());
    return out;
}

HashBytes hash_from_hex(const std::string& hex) {
    HashBytes out{};
    auto bytes = from_hex(hex);
    if (bytes.size() != out.size()) {
        return out;
    }
    std::memcpy(out.data(), bytes.data(), out.size());
    return out;
}

} // namespace core::crypto
