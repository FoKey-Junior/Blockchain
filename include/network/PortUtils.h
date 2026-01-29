#ifndef PORT_UTILS_H
#define PORT_UTILS_H

#include <asio.hpp>
#include <optional>
#include <cstdint>
#include <iostream>
#include <string>

// Диапазоны портов (малоиспользуемые, чтобы чаще были свободны)
// Майнер: свой диапазон
constexpr uint16_t MINER_PORT_MIN = 39100;
constexpr uint16_t MINER_PORT_MAX = 39149;

// Сервер (main_server): свой диапазон
constexpr uint16_t SERVER_PORT_MIN = 39150;
constexpr uint16_t SERVER_PORT_MAX = 39199;

// Клиент: свой диапазон
constexpr uint16_t CLIENT_PORT_MIN = 39200;
constexpr uint16_t CLIENT_PORT_MAX = 39299;

// Порт сервера, к которому подключается клиент (должен совпадать с тем, на котором слушает main_server)
constexpr uint16_t SERVER_CONNECT_PORT = 39150;

// Хост сервера по умолчанию для клиента
constexpr const char* SERVER_CONNECT_HOST = "213.176.117.68";

/** Ищет первый свободный порт в диапазоне [start_port, end_port].
 *  Если порт занят, пробует следующий — программа продолжит работу через другой порт. */
inline std::optional<uint16_t> find_free_port(uint16_t start_port, uint16_t end_port) {
    for (uint16_t p = start_port; p <= end_port; ++p) {
        asio::io_context ctx;
        asio::ip::tcp::acceptor acceptor(ctx);
        asio::error_code ec;
        acceptor.open(asio::ip::tcp::v4(), ec);
        if (ec) continue;
        acceptor.bind(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), p), ec);
        if (ec) {
            if (ec == asio::error::address_in_use) {
                std::cout << "[PortUtils] Port " << p << " is busy, trying next...\n";
            }
            continue;
        }
        acceptor.close(ec);
        return p;
    }
    return std::nullopt;
}

#endif
