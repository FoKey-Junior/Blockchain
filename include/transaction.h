#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "types.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>
#include <optional>
#include <cstdint>

class transaction {
private:
    address_bytes address_;
    signature_bytes signature_;
    address_bytes sender_address_;
    address_bytes receiver_address_;
    std::unordered_map<std::string, file_metadata> files_;
    std::chrono::system_clock::time_point creation_time_;

    void compute_address() noexcept;

public:
    transaction(
        const address_bytes& sender_address,
        const address_bytes& receiver_address,
        std::unordered_map<std::string, file_metadata> files
    ) noexcept;

    transaction(
        const address_bytes& address,
        const signature_bytes& signature,
        const address_bytes& sender_address,
        const address_bytes& receiver_address,
        std::unordered_map<std::string, file_metadata> files,
        std::chrono::system_clock::time_point creation_time
    ) noexcept;

    ~transaction() noexcept;

    transaction(const transaction&) = default;
    transaction& operator=(const transaction&) = default;
    transaction(transaction&&) noexcept = default;
    transaction& operator=(transaction&&) noexcept = default;

    void sign(const private_key_bytes& sender_private_key) noexcept(false);
    [[nodiscard]] bool verify(const public_key_bytes& sender_public_key) const noexcept;

    [[nodiscard]] const address_bytes& get_address() const noexcept { return address_; }
    [[nodiscard]] const address_bytes& get_sender_address() const noexcept { return sender_address_; }
    [[nodiscard]] const address_bytes& get_receiver_address() const noexcept { return receiver_address_; }
    [[nodiscard]] const std::unordered_map<std::string, file_metadata>& get_files() const noexcept { return files_; }
    [[nodiscard]] std::chrono::system_clock::time_point get_creation_time() const noexcept { return creation_time_; }

    [[nodiscard]] std::vector<std::uint8_t> serialize() const noexcept;
    [[nodiscard]] static std::optional<transaction> deserialize(const std::vector<std::uint8_t>& data) noexcept;
};

#endif

