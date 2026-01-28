#include <cstring>
#include <sodium.h>
#include "../../include/blockchain/Block.h"
#include <vector>
#include <optional>

Block::Block(
    const unsigned char* address_,
    const unsigned char* previous_address_,
    const unsigned char* sender_,
    const unsigned char* receiver_,
    std::chrono::system_clock::time_point time_creation_,
    const std::unordered_map<std::string, FileMetadata>& files_
) : time_creation(time_creation_), files(files_) {
    std::memcpy(this->address, address_, crypto_generichash_BYTES);
    std::memcpy(this->previous_address, previous_address_, crypto_generichash_BYTES);
    std::memcpy(this->sender, sender_, crypto_generichash_BYTES);
    std::memcpy(this->receiver, receiver_, crypto_generichash_BYTES);
}

std::vector<uint8_t> Block::serialize() const noexcept {
    std::vector<uint8_t> buf;

    buf.insert(buf.end(), address, address + crypto_generichash_BYTES);
    buf.insert(buf.end(), previous_address, previous_address + crypto_generichash_BYTES);
    buf.insert(buf.end(), sender, sender + crypto_generichash_BYTES);
    buf.insert(buf.end(), receiver, receiver + crypto_generichash_BYTES);

    // Время создания (как int64_t секунды с epoch)
    auto time_t = std::chrono::system_clock::to_time_t(time_creation);
    int64_t time_seconds = static_cast<int64_t>(time_t);
    buf.insert(buf.end(), reinterpret_cast<const uint8_t*>(&time_seconds),
               reinterpret_cast<const uint8_t*>(&time_seconds) + sizeof(int64_t));

    // Количество файлов
    uint32_t file_count = static_cast<uint32_t>(files.size());
    buf.insert(buf.end(), reinterpret_cast<const uint8_t*>(&file_count),
               reinterpret_cast<const uint8_t*>(&file_count) + sizeof(uint32_t));

    // Файлы (для простоты только хеши)
    for (const auto& [name, file] : files) {
        buf.insert(buf.end(), file.content.begin(), file.content.end());
    }

    return buf;
}

std::optional<Block> Block::deserialize(const std::vector<uint8_t>& data) noexcept {
    size_t offset = 0;

    unsigned char addr[crypto_generichash_BYTES];
    unsigned char prev_addr[crypto_generichash_BYTES];
    unsigned char sender_addr[crypto_generichash_BYTES];
    unsigned char receiver_addr[crypto_generichash_BYTES];

    int64_t time_seconds;
    uint32_t file_count;

    if (!read_bytes(data, offset, addr, crypto_generichash_BYTES) ||
        !read_bytes(data, offset, prev_addr, crypto_generichash_BYTES) ||
        !read_bytes(data, offset, sender_addr, crypto_generichash_BYTES) ||
        !read_bytes(data, offset, receiver_addr, crypto_generichash_BYTES) ||
        !read_bytes(data, offset, &time_seconds, sizeof(time_seconds)) ||
        !read_bytes(data, offset, &file_count, sizeof(file_count))) {
        return std::nullopt;
        }

    auto time_creation = std::chrono::system_clock::from_time_t(time_seconds);

    std::unordered_map<std::string, FileMetadata> files_map;
    for (uint32_t i = 0; i < file_count; ++i) {
        FileMetadata file;
        if (!read_bytes(
                data,
                offset,
                file.content.data(),
                crypto_hash_sha256_BYTES)) {
            return std::nullopt;
                }

        files_map.emplace("file_" + std::to_string(i), file);
    }

    return Block(addr, prev_addr, sender_addr, receiver_addr, time_creation, files_map);
}
