#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <vector>
#include <cstdint>
#include "types.h"

class crypto_utils {
public:
    static std::vector<std::uint8_t> sign_message(
        const std::vector<std::uint8_t>& message,
        const private_key_bytes& private_key
    ) noexcept;

    static bool verify_message(
        const std::vector<std::uint8_t>& signed_message,
        const public_key_bytes& public_key,
        std::vector<std::uint8_t>& output_message
    ) noexcept;

    static void compute_address(
        const public_key_bytes& public_key,
        address_bytes& output_address
    ) noexcept;

    static void compute_file_hash(
        const std::vector<std::uint8_t>& file_data,
        hash_bytes& output_hash
    ) noexcept;

    static bool verify_file_integrity(
        const std::vector<std::uint8_t>& file_data,
        const hash_bytes& expected_hash
    ) noexcept;
};

#endif

