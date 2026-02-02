#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <asio.hpp>
#include <optional>
#include <cstdint>

constexpr std::uint16_t miner_port_min = 39100;
constexpr std::uint16_t miner_port_max = 39149;
constexpr std::uint16_t server_port_min = 39150;
constexpr std::uint16_t server_port_max = 39199;
constexpr std::uint16_t client_port_min = 39200;
constexpr std::uint16_t client_port_max = 39299;
constexpr std::uint16_t server_connect_port = 39150;
constexpr const char* server_connect_host = "213.176.117.68";

[[nodiscard]] std::optional<std::uint16_t> find_free_port(std::uint16_t start_port, std::uint16_t end_port) noexcept;

#endif

