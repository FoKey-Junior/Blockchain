#include <iostream>
#include <thread>
#include <asio.hpp>
#include "blockchain/Blockchain.h"
#include "blockchain/Miner.h"
#include "blockchain/User.h"
#include "network/Node.h"
#include "api/Api.h"

int main() {
    // Инициализация libsodium
    if (sodium_init() < 0) {
        std::cerr << "libsodium init failed\n";
        return 1;
    }

    // Создаем пользователя-майнера
    User miner_user;

    // Массив мемпула
    std::vector<Transaction> mempool_vec;

    // Блокчейн
    Blockchain blockchain(miner_user.get_address_bytes());

    // Майнер
    Miner miner(mempool_vec);
    miner.set_blockchain(&blockchain);

    // io_context и Node
    asio::io_context io;
    Node node(io, 12345, miner_user.get_public_key(), miner_user.get_private_key());
    node.set_mempool(&mempool_vec);
    node.set_blockchain(&blockchain);
    node.set_miner(&miner);

    // Запуск Node (асинхронно)
    node.start();

    // Запуск майнинга в отдельном потоке
    std::thread mining_thread([&miner]() {
        miner.start_mining();
    });
    mining_thread.detach();

    std::cout << "Server node started on port 12345\n";

    // Запуск io_context (сеть)
    io.run();

    return 0;
}