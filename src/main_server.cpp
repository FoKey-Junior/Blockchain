#include <iostream>
#include <thread>
#include <asio.hpp>
#include "blockchain/Blockchain.h"
#include "blockchain/Miner.h"
#include "blockchain/User.h"
#include "network/Node.h"

int main() {
    User miner_user;
    std::vector<Transaction> mempool_vec;
    Blockchain blockchain(miner_user.get_address_bytes());
    Miner miner(mempool_vec);
    miner.set_blockchain(&blockchain);

    if (sodium_init() < 0) {
        std::cerr << "libsodium init failed\n";
        return 1;
    }

    asio::io_context io;
    Node node(io, 12345, miner_user.get_public_key(), miner_user.get_private_key());
    node.set_mempool(&mempool_vec);
    node.set_blockchain(&blockchain);
    node.set_miner(&miner);
    node.start();

    std::thread mining_thread([&miner]() {
        miner.start_mining();
    });

    mining_thread.detach();

    std::cout << "========================================\n";
    std::cout << "Server node started on port 12345\n";
    std::cout << "Waiting for connections...\n";
    std::cout << "========================================\n";

    io.run();

    return 0;
}