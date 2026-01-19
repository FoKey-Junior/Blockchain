#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H

#include <sodium.h>
#include <iostream>
#include <cstring>
#include <chrono>
#include <unordered_map>

struct FileMetadata {
    std::array<unsigned char, crypto_hash_sha256_BYTES> content;
};

class Transaction {
    unsigned char address[crypto_generichash_BYTES] = {};
    unsigned char signature[crypto_sign_BYTES] = {};
    std::chrono::system_clock::time_point time_creation;
    unsigned char sender[crypto_generichash_BYTES] = {};
    unsigned char receiver[crypto_generichash_BYTES] = {};
    std::unordered_map<std::string, FileMetadata> files;

public:
    Transaction(
        const unsigned char* sender_,
        const unsigned char* receiver_,
        std::unordered_map<std::string, FileMetadata> files_
    );

    void sign(const unsigned char* sender_private_key);
    bool verify(const unsigned char* sender_public_key) const;
    void print() const;

    const unsigned char* get_address_bytes() const { return address; }

    ~Transaction();
};


#endif