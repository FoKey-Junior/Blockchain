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
    constexpr size_t min_size = crypto_generichash_BYTES * 4 + sizeof(int64_t) + sizeof(uint32_t);
    if (data.size() < min_size) {
        return std::nullopt;
    }
    
    size_t offset = 0;
    
    // Адрес блока
    unsigned char addr[crypto_generichash_BYTES];
    std::memcpy(addr, data.data() + offset, crypto_generichash_BYTES);
    offset += crypto_generichash_BYTES;
    
    // Адрес предыдущего блока
    unsigned char prev_addr[crypto_generichash_BYTES];
    std::memcpy(prev_addr, data.data() + offset, crypto_generichash_BYTES);
    offset += crypto_generichash_BYTES;
    
    // Адрес отправителя
    unsigned char sender_addr[crypto_generichash_BYTES];
    std::memcpy(sender_addr, data.data() + offset, crypto_generichash_BYTES);
    offset += crypto_generichash_BYTES;
    
    // Адрес получателя
    unsigned char receiver_addr[crypto_generichash_BYTES];
    std::memcpy(receiver_addr, data.data() + offset, crypto_generichash_BYTES);
    offset += crypto_generichash_BYTES;
    
    // Время создания
    int64_t time_seconds;
    std::memcpy(&time_seconds, data.data() + offset, sizeof(int64_t));
    offset += sizeof(int64_t);
    auto time_creation = std::chrono::system_clock::from_time_t(time_seconds);
    
    // Количество файлов
    uint32_t file_count;
    std::memcpy(&file_count, data.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    
    std::unordered_map<std::string, FileMetadata> files_map;
    for (uint32_t i = 0; i < file_count; ++i) {
        if (offset + crypto_hash_sha256_BYTES > data.size()) {
            return std::nullopt;
        }
        FileMetadata file;
        std::memcpy(file.content.data(), data.data() + offset, crypto_hash_sha256_BYTES);
        offset += crypto_hash_sha256_BYTES;
        files_map["file_" + std::to_string(i)] = file;
    }
    
    return Block(addr, prev_addr, sender_addr, receiver_addr, time_creation, files_map);
}
