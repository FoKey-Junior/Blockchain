#include "../include/port_utils.h"
#include <iostream>

std::optional<std::uint16_t> find_free_port(std::uint16_t start_port, std::uint16_t end_port) noexcept {
    for (std::uint16_t port = start_port; port <= end_port; ++port) {
        asio::io_context context;
        asio::ip::tcp::acceptor acceptor(context);
        std::error_code error_code;
        
        acceptor.open(asio::ip::tcp::v4(), error_code);
        if (error_code) {
            continue;
        }
        
        acceptor.bind(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port), error_code);
        if (error_code) {
            if (error_code == asio::error::address_in_use) {
                std::cout << "[PortUtils] Port " << port << " is busy, trying next...\n";
            }
            continue;
        }
        
        acceptor.close(error_code);
        return port;
    }
    
    return std::nullopt;
}

