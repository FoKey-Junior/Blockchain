#ifndef BLOCK_H
#define BLOCK_H

#include "types.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>
#include <optional>
#include <cstdint>

class block {
private:
    address_bytes address_;
    address_bytes previous_address_;
    address_bytes sender_address_;
    address_bytes receiver_address_;
    std::chrono::system_clock::time_point creation_time_;
    std::unordered_map<std::string, file_metadata> files_;

public:
    block(
        const address_bytes& address,
        const address_bytes& previous_address,
        const address_bytes& sender_address,
        const address_bytes& receiver_address,
        std::chrono::system_clock::time_point creation_time,
        std::unordered_map<std::string, file_metadata> files
    ) noexcept;

    block(const block&) = default;
    block& operator=(const block&) = default;
    block(block&&) noexcept = default;
    block& operator=(block&&) noexcept = default;
    ~block() = default;

    [[nodiscard]] const address_bytes& get_address() const noexcept { return address_; }
    [[nodiscard]] const address_bytes& get_previous_address() const noexcept { return previous_address_; }
    [[nodiscard]] const address_bytes& get_sender_address() const noexcept { return sender_address_; }
    [[nodiscard]] const address_bytes& get_receiver_address() const noexcept { return receiver_address_; }
    [[nodiscard]] const std::unordered_map<std::string, file_metadata>& get_files() const noexcept { return files_; }
    [[nodiscard]] std::chrono::system_clock::time_point get_creation_time() const noexcept { return creation_time_; }

    [[nodiscard]] std::vector<std::uint8_t> serialize() const noexcept;
    [[nodiscard]] static std::optional<block> deserialize(const std::vector<std::uint8_t>& data) noexcept;
};

#endif

