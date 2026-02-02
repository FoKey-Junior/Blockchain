#include "../include/transaction.h"
#include <sodium.h>
#include <cstring>
#include <algorithm>

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

transaction::transaction(
    const address_bytes& sender_address,
    const address_bytes& receiver_address,
    std::unordered_map<std::string, file_metadata> files
) noexcept : sender_address_(sender_address),
              receiver_address_(receiver_address),
              files_(std::move(files)),
              creation_time_(std::chrono::system_clock::now()) {
    compute_address();
}

transaction::transaction(
    const address_bytes& address,
    const signature_bytes& signature,
    const address_bytes& sender_address,
    const address_bytes& receiver_address,
    std::unordered_map<std::string, file_metadata> files,
    std::chrono::system_clock::time_point creation_time
) noexcept : address_(address),
              signature_(signature),
              sender_address_(sender_address),
              receiver_address_(receiver_address),
              files_(std::move(files)),
              creation_time_(creation_time) {
}

transaction::~transaction() noexcept {
    sodium_memzero(sender_address_.data(), sender_address_.size());
    sodium_memzero(receiver_address_.data(), receiver_address_.size());
    sodium_memzero(address_.data(), address_.size());
    sodium_memzero(signature_.data(), signature_.size());
}

void transaction::compute_address() noexcept {
    const auto time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        creation_time_.time_since_epoch()).count();
    
    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);
    crypto_generichash_update(&state, sender_address_.data(), sender_address_.size());
    crypto_generichash_update(&state, receiver_address_.data(), receiver_address_.size());
    crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(&time_ns), sizeof(time_ns));
    crypto_generichash_final(&state, address_.data(), address_.size());
}

void transaction::sign(const private_key_bytes& sender_private_key) noexcept(false) {
    unsigned long long signature_length = 0;
    
    if (crypto_sign_detached(signature_.data(), &signature_length,
                             address_.data(), address_.size(),
                             sender_private_key.data()) != 0) {
        throw std::runtime_error("Failed to sign transaction");
    }
}

bool transaction::verify(const public_key_bytes& sender_public_key) const noexcept {
    return crypto_sign_verify_detached(signature_.data(),
                                       address_.data(), address_.size(),
                                       sender_public_key.data()) == 0;
}

std::vector<std::uint8_t> transaction::serialize() const noexcept {
    std::vector<std::uint8_t> buffer;
    buffer.reserve(crypto_generichash_BYTES * 3 + crypto_sign_BYTES + 
                   sizeof(std::int64_t) + sizeof(std::uint32_t) +
                   files_.size() * (sizeof(std::uint32_t) + crypto_hash_sha256_BYTES));

    buffer.insert(buffer.end(), address_.begin(), address_.end());
    buffer.insert(buffer.end(), signature_.begin(), signature_.end());
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

std::optional<transaction> transaction::deserialize(const std::vector<std::uint8_t>& data) noexcept {
    constexpr std::size_t min_size = crypto_generichash_BYTES * 3 + crypto_sign_BYTES + 
                                     sizeof(std::int64_t) + sizeof(std::uint32_t);
    if (data.size() < min_size) {
        return std::nullopt;
    }

    std::size_t offset = 0;
    address_bytes address;
    signature_bytes signature;
    address_bytes sender_address;
    address_bytes receiver_address;
    std::int64_t time_seconds = 0;
    std::uint32_t file_count = 0;

    if (!read_bytes(data, offset, address.data(), crypto_generichash_BYTES) ||
        !read_bytes(data, offset, signature.data(), crypto_sign_BYTES) ||
        !read_bytes(data, offset, sender_address.data(), crypto_generichash_BYTES) ||
        !read_bytes(data, offset, receiver_address.data(), crypto_generichash_BYTES) ||
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
        if (!read_bytes(data, offset, file.content_hash.data(), crypto_hash_sha256_BYTES)) {
            return std::nullopt;
        }

        files.emplace(std::move(name), std::move(file));
    }

    return transaction(address, signature, sender_address, receiver_address, 
                      std::move(files), creation_time);
}

