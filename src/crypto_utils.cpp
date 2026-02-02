#include "../include/crypto_utils.h"
#include <sodium.h>
#include <cstring>
#include <array>
#include <tuple>

std::vector<std::uint8_t> crypto_utils::sign_message(
    const std::vector<std::uint8_t>& message,
    const private_key_bytes& private_key
) noexcept {
    std::vector<std::uint8_t> signed_message(message.size() + crypto_sign_BYTES);
    unsigned long long signed_length = 0;
    
    if (crypto_sign(signed_message.data(), &signed_length,
                    message.data(), message.size(),
                    private_key.data()) != 0) {
        return {};
    }
    
    signed_message.resize(signed_length);
    return signed_message;
}

bool crypto_utils::verify_message(
    const std::vector<std::uint8_t>& signed_message,
    const public_key_bytes& public_key,
    std::vector<std::uint8_t>& output_message
) noexcept {
    output_message.resize(signed_message.size());
    unsigned long long output_length = 0;
    
    if (crypto_sign_open(output_message.data(), &output_length,
                         signed_message.data(), signed_message.size(),
                         public_key.data()) != 0) {
        return false;
    }
    
    output_message.resize(output_length);
    return true;
}

void crypto_utils::compute_address(
    const public_key_bytes& public_key,
    address_bytes& output_address
) noexcept {
    crypto_generichash(output_address.data(), output_address.size(),
                      public_key.data(), public_key.size(),
                      nullptr, 0);
}

void crypto_utils::compute_file_hash(
    const std::vector<std::uint8_t>& file_data,
    hash_bytes& output_hash
) noexcept {
    crypto_hash_sha256(output_hash.data(), file_data.data(), file_data.size());
}

bool crypto_utils::verify_file_integrity(
    const std::vector<std::uint8_t>& file_data,
    const hash_bytes& expected_hash
) noexcept {
    hash_bytes computed_hash;
    compute_file_hash(file_data, computed_hash);
    return std::memcmp(computed_hash.data(), expected_hash.data(), crypto_hash_sha256_BYTES) == 0;
}

