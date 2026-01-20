#include "mining_window.h"
#include "./ui_mining_window.h"

#include <asio.hpp>
#include <sodium.h>
#include <iostream>

#include "network/Node.h"
#include "blockchain/Blockchain.h"
#include "blockchain/Miner.h"
#include "blockchain/Mempool.h"
#include "blockchain/User.h"


MiningWindow::MiningWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MiningWindow)
{
    ui->setupUi(this);

    // 🔐 Личность майнера
    User miner_user;

    asio::io_context io;

    // 🌐 Узел сети
    Node node(
        io,
        12345,                         // порт
        miner_user.get_public_key(),
        miner_user.get_private_key()
    );

    // ⛓ Блокчейн
    Blockchain blockchain;

    // 📦 Mempool
    Mempool mempool;

    // ⛏ Майнер
    Miner miner(
        miner_user,
        blockchain,
        mempool,
        node
    );

    // 🔌 Связи
    node.set_mempool(&mempool);
    node.set_blockchain(&blockchain);
    node.set_miner(&miner);

    // ▶ Запуск
    node.start();

    std::thread mining_thread([&] {
        miner.start_mining();
    });

    std::cout << "Miner node started\n";

    io.run();
    mining_thread.join();
}

MiningWindow::~MiningWindow()
{
    delete ui;
}
