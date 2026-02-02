#ifndef PEER_H
#define PEER_H

#include "types.h"
#include <string>
#include <chrono>
#include <cstdint>

class peer {
private:
    std::string ip_address_;
    std::uint16_t port_;
    std::chrono::steady_clock::time_point last_activity_;
    public_key_bytes public_key_;

public:
    peer(const std::string& ip_address, std::uint16_t port, const public_key_bytes& public_key) noexcept;
    ~peer() noexcept;

    peer(const peer&) = default;
    peer& operator=(const peer&) = default;
    peer(peer&&) noexcept = default;
    peer& operator=(peer&&) noexcept = default;

    [[nodiscard]] const std::string& get_ip_address() const noexcept { return ip_address_; }
    [[nodiscard]] std::uint16_t get_port() const noexcept { return port_; }
    [[nodiscard]] std::chrono::steady_clock::time_point get_last_activity() const noexcept { return last_activity_; }
    [[nodiscard]] const public_key_bytes& get_public_key() const noexcept { return public_key_; }

    void update_last_activity() noexcept { last_activity_ = std::chrono::steady_clock::now(); }
};

#endif

