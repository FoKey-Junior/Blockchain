#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H

#include <unordered_map>
#include <chrono>
#include <vector>
#include <optional>
#include "Block.h"

class Transaction {
    unsigned char address[crypto_generichash_BYTES] = {};
    unsigned char signature[crypto_sign_BYTES] = {};
    std::chrono::system_clock::time_point time_creation;
    unsigned char sender[crypto_generichash_BYTES] = {};
    unsigned char receiver[crypto_generichash_BYTES] = {};
    std::unordered_map<std::string, FileMetadata> files;

    Transaction(
        const unsigned char* address_,
        const unsigned char* signature_,
        const unsigned char* sender_,
        const unsigned char* receiver_,
        std::unordered_map<std::string, FileMetadata> files_,
        std::chrono::system_clock::time_point time_
    );

public:
    Transaction(
        const unsigned char* sender_,
        const unsigned char* receiver_,
        std::unordered_map<std::string, FileMetadata> files_
    );

    ~Transaction();

    void sign_transaction(const unsigned char* sender_private_key);
    bool verify_transaction(const unsigned char* sender_public_key) const;
    [[nodiscard]] const unsigned char* get_address_bytes() const;
    [[nodiscard]] const unsigned char* get_sender() const;
    [[nodiscard]] const unsigned char* get_receiver() const;
    [[nodiscard]] const std::unordered_map<std::string, FileMetadata>& get_files() const;
    [[nodiscard]] std::vector<uint8_t> serialize() const noexcept;
    static std::optional<Transaction> deserialize(const std::vector<uint8_t>& data) noexcept;
};


#endif