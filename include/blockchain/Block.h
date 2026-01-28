#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H


#include <sodium.h>
#include <cstring>
#include <unordered_map>
#include <chrono>
#include <array>
#include <string>
#include <vector>
#include <optional>

struct FileMetadata {
    std::array<unsigned char, crypto_hash_sha256_BYTES> content;
};

static bool read_bytes(
    const std::vector<uint8_t>& data,
    size_t& offset,
    void* dst,
    size_t size
) {
    if (offset + size > data.size()) {
        return false;
    }
    std::memcpy(dst, data.data() + offset, size);
    offset += size;
    return true;
}

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

    [[nodiscard]] const unsigned char* get_address() const { return address; }
    [[nodiscard]] const unsigned char* get_previous_address() const { return previous_address; }
    [[nodiscard]] const unsigned char* get_sender() const { return sender; }
    [[nodiscard]] const unsigned char* get_receiver() const { return receiver; }
    [[nodiscard]] const std::unordered_map<std::string, FileMetadata>& get_files() const { return files; }
    [[nodiscard]] const std::chrono::system_clock::time_point& get_time() const { return time_creation; }

    [[nodiscard]] std::vector<uint8_t> serialize() const noexcept;
    static std::optional<Block> deserialize(const std::vector<uint8_t>& data) noexcept;
};

#endif
