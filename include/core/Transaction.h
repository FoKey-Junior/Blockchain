#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H

#include <array>
#include <cstdint>
#include <string>
#include <sodium.h>

class Transaction {
    unsigned char sender[crypto_generichash_BYTES]{};
    unsigned char receiver[crypto_generichash_BYTES]{};
    unsigned char hash[crypto_generichash_BYTES]{};
    unsigned char signature[crypto_sign_BYTES]{};

    uint64_t timestamp{};
    uint64_t amount{};

public:
    Transaction(const unsigned char* sender_data,
                const unsigned char* receiver_data,
                uint64_t amount);

    const unsigned char* get_hash() const noexcept { return hash; }
    std::string get_hash_hex() const;

    void sign(const unsigned char* sender_private_key);
    bool verify(const unsigned char* sender_public_key) const noexcept;

    void print() const;
    ~Transaction();
};

#endif
