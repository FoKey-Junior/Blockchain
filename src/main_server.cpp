#include <iostream>
#include <thread>
#include <asio.hpp>
#include <sodium.h>
#include "../include/user.h"
#include "../include/mempool.h"
#include "../include/blockchain.h"
#include "../include/miner.h"
#include "../include/node.h"
#include "../include/port_utils.h"

int main() {
    if (sodium_init() < 0) {
        std::cerr << "libsodium init failed\n";
        return 1;
    }

    user miner_user;
    mempool mempool_instance;
    blockchain blockchain_instance(miner_user.get_address_bytes());
    miner miner_instance(mempool_instance);
    miner_instance.set_blockchain(&blockchain_instance);

    const auto port_opt = find_free_port(server_port_min, server_port_max);
    if (!port_opt.has_value()) {
        std::cerr << "No free server port in range " << server_port_min << "-" << server_port_max << "\n";
        return 1;
    }

    const std::uint16_t server_port = port_opt.value();
    std::cout << "[Server] Using port " << server_port << "\n";

    asio::io_context io_context;
    node node_instance(io_context, server_port,
                      miner_user.get_public_key(), miner_user.get_private_key());
    node_instance.set_blockchain(&blockchain_instance);
    node_instance.set_mempool(&mempool_instance);
    node_instance.set_miner(&miner_instance);
    miner_instance.set_node(&node_instance);
    node_instance.start();

    miner_instance.start();

    std::cout << "========================================\n";
    std::cout << "Server node started on port " << server_port << "\n";
    std::cout << "Clients should connect to host:port " << server_port << "\n";
    std::cout << "Waiting for connections...\n";
    std::cout << "========================================\n";

    io_context.run();

    return 0;
}
