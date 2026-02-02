#ifndef USER_H
#define USER_H

#include "types.h"
#include <string>
#include <chrono>

class user {
private:
    public_key_bytes public_key_;
    private_key_bytes private_key_;
    address_bytes address_bytes_;
    std::string address_string_;
    std::chrono::system_clock::time_point creation_time_;

    void initialize_keys() noexcept;
    void compute_address() noexcept;

public:
    user() noexcept;
    ~user() noexcept;

    user(const user&) = delete;
    user& operator=(const user&) = delete;
    user(user&&) noexcept = default;
    user& operator=(user&&) noexcept = default;

    [[nodiscard]] const private_key_bytes& get_private_key() const noexcept { return private_key_; }
    [[nodiscard]] const public_key_bytes& get_public_key() const noexcept { return public_key_; }
    [[nodiscard]] const address_bytes& get_address_bytes() const noexcept { return address_bytes_; }
    [[nodiscard]] const std::string& get_address_string() const noexcept { return address_string_; }
    [[nodiscard]] std::chrono::system_clock::time_point get_creation_time() const noexcept { return creation_time_; }
};

#endif

