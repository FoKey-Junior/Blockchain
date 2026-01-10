#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H


#include <iostream>
#include <sodium.h>
#include <cstring>
#include <chrono>

class Transaction {
    unsigned char sender[crypto_generichash_BYTES] = {};
    unsigned char receiver[crypto_generichash_BYTES] = {};
    unsigned char address[crypto_generichash_BYTES] = {};
    unsigned char signature[crypto_sign_BYTES] = {};
    std::chrono::system_clock::time_point time_creation;
    uint64_t amount;

public:
    Transaction(
        const unsigned char* sender_data,
        const unsigned char* receiver_data,
        const uint64_t amount
    );

    std::array<unsigned char, crypto_generichash_BYTES> get_address_array() const {
        std::array<unsigned char, crypto_generichash_BYTES> arr{};
        std::memcpy(arr.data(), address, crypto_generichash_BYTES);
        return arr;
    }

    void sign(const unsigned char* sender_private_key);
    bool verify(const unsigned char* sender_public_key) const;
    void print() const;

    ~Transaction();
};


#endif