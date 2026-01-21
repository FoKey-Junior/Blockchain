#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <sodium.h>
#include <unordered_map>
#include <chrono>
#include <array>
#include <string>

struct FileMetadata {
    std::array<unsigned char, crypto_hash_sha256_BYTES> content;
};

class Block {
private:
    unsigned char address[crypto_generichash_BYTES] = {};
    unsigned char previous_address[crypto_generichash_BYTES] = {};
    unsigned char sender[crypto_generichash_BYTES] = {};
    unsigned char receiver[crypto_generichash_BYTES] = {};
    std::chrono::system_clock::time_point time_creation;
    std::unordered_map<std::string, FileMetadata> files;

public:
    Block(const unsigned char* address_,
          const unsigned char* previous_address_,
          const unsigned char* sender_,
          const unsigned char* receiver_,
          std::chrono::system_clock::time_point time_creation_,
          const std::unordered_map<std::string, FileMetadata>& files_);

    const unsigned char* get_address() const { return address; }
    const unsigned char* get_sender() const { return sender; }
    const unsigned char* get_receiver() const { return receiver; }
    const std::unordered_map<std::string, FileMetadata>& get_files() const { return files; }
    const std::chrono::system_clock::time_point& get_time() const { return time_creation; }
};

#endif
