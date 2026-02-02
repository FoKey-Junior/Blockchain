#include "../include/block.h"
#include <cstring>

namespace {
    bool read_bytes(
        const std::vector<std::uint8_t>& data,
        std::size_t& offset,
        void* destination,
        std::size_t size
    ) noexcept {
        if (offset + size > data.size()) {
            return false;
        }
        std::memcpy(destination, data.data() + offset, size);
        offset += size;
        return true;
    }
}

block::block(
    const address_bytes& address,
    const address_bytes& previous_address,
    const address_bytes& sender_address,
    const address_bytes& receiver_address,
    std::chrono::system_clock::time_point creation_time,
    std::unordered_map<std::string, file_metadata> files
) noexcept : address_(address),
             previous_address_(previous_address),
             sender_address_(sender_address),
             receiver_address_(receiver_address),
             creation_time_(creation_time),
             files_(std::move(files)) {
}

std::vector<std::uint8_t> block::serialize() const noexcept {
    std::vector<std::uint8_t> buffer;
    buffer.reserve(address_bytes::size() * 4 + sizeof(std::int64_t) + 
                   sizeof(std::uint32_t) + files_.size() * (sizeof(std::uint32_t) + hash_bytes::size()));

    buffer.insert(buffer.end(), address_.begin(), address_.end());
    buffer.insert(buffer.end(), previous_address_.begin(), previous_address_.end());
    buffer.insert(buffer.end(), sender_address_.begin(), sender_address_.end());
    buffer.insert(buffer.end(), receiver_address_.begin(), receiver_address_.end());

    const auto time_seconds = std::chrono::duration_cast<std::chrono::seconds>(
        creation_time_.time_since_epoch()).count();
    const std::int64_t time_value = static_cast<std::int64_t>(time_seconds);
    buffer.insert(buffer.end(), reinterpret_cast<const std::uint8_t*>(&time_value),
                  reinterpret_cast<const std::uint8_t*>(&time_value) + sizeof(time_value));

    const std::uint32_t file_count = static_cast<std::uint32_t>(files_.size());
    buffer.insert(buffer.end(), reinterpret_cast<const std::uint8_t*>(&file_count),
                  reinterpret_cast<const std::uint8_t*>(&file_count) + sizeof(file_count));

    for (const auto& [name, file] : files_) {
        const std::uint32_t name_length = static_cast<std::uint32_t>(name.size());
        buffer.insert(buffer.end(), reinterpret_cast<const std::uint8_t*>(&name_length),
                      reinterpret_cast<const std::uint8_t*>(&name_length) + sizeof(name_length));
        buffer.insert(buffer.end(), name.begin(), name.end());
        buffer.insert(buffer.end(), file.content_hash.begin(), file.content_hash.end());
    }

    return buffer;
}

std::optional<block> block::deserialize(const std::vector<std::uint8_t>& data) noexcept {
    constexpr std::size_t min_size = address_bytes::size() * 4 + sizeof(std::int64_t) + sizeof(std::uint32_t);
    if (data.size() < min_size) {
        return std::nullopt;
    }

    std::size_t offset = 0;
    address_bytes address;
    address_bytes previous_address;
    address_bytes sender_address;
    address_bytes receiver_address;
    std::int64_t time_seconds = 0;
    std::uint32_t file_count = 0;

    if (!read_bytes(data, offset, address.data(), address_bytes::size()) ||
        !read_bytes(data, offset, previous_address.data(), address_bytes::size()) ||
        !read_bytes(data, offset, sender_address.data(), address_bytes::size()) ||
        !read_bytes(data, offset, receiver_address.data(), address_bytes::size()) ||
        !read_bytes(data, offset, &time_seconds, sizeof(time_seconds)) ||
        !read_bytes(data, offset, &file_count, sizeof(file_count))) {
        return std::nullopt;
    }

    const auto creation_time = std::chrono::system_clock::from_time_t(time_seconds);
    std::unordered_map<std::string, file_metadata> files;

    for (std::uint32_t i = 0; i < file_count; ++i) {
        std::uint32_t name_length = 0;
        if (!read_bytes(data, offset, &name_length, sizeof(name_length))) {
            return std::nullopt;
        }

        if (offset + name_length > data.size()) {
            return std::nullopt;
        }

        std::string name(reinterpret_cast<const char*>(data.data() + offset), name_length);
        offset += name_length;

        file_metadata file;
        if (!read_bytes(data, offset, file.content_hash.data(), hash_bytes::size())) {
            return std::nullopt;
        }

        files.emplace(std::move(name), std::move(file));
    }

    return block(address, previous_address, sender_address, receiver_address,
                creation_time, std::move(files));
}

