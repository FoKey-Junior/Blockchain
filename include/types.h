#ifndef TYPES_H
#define TYPES_H

#include <sodium.h>
#include <array>
#include <cstdint>

using address_bytes = std::array<unsigned char, crypto_generichash_BYTES>;
using public_key_bytes = std::array<unsigned char, crypto_sign_PUBLICKEYBYTES>;
using private_key_bytes = std::array<unsigned char, crypto_sign_SECRETKEYBYTES>;
using signature_bytes = std::array<unsigned char, crypto_sign_BYTES>;
using hash_bytes = std::array<unsigned char, crypto_hash_sha256_BYTES>;

struct file_metadata {
    hash_bytes content_hash;
};

#endif

