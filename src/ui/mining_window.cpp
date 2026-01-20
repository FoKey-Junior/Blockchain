#include "mining_window.h"
#include "./ui_mining_window.h"

#include "../../include/blockchain/User.h"
#include "../../include/blockchain/Blockchain.h"
#include "../../include/blockchain/Miner.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/network/Node.h"

#include <asio.hpp>
#include <thread>
#include <iostream>

MiningWindow::MiningWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MiningWindow)
{
    ui->setupUi(this);

    User miner_user;

    io_context = std::make_unique<asio::io_context>();
    node = std::make_unique<Node>(*io_context, 12345, miner_user.get_public_key(), miner_user.get_private_key());

    mempool_vec = std::make_unique<std::vector<Transaction>>();
    blockchain = std::make_unique<Blockchain>(miner_user.get_address_bytes());
    miner = std::make_unique<Miner>(*mempool_vec);
    miner->set_blockchain(blockchain.get());

    node->set_mempool(mempool_vec.get());
    node->set_blockchain(blockchain.get());
    node->set_miner(miner.get());

    node->start();

    std::thread([this]() { miner->start_mining(); }).detach();
    std::thread([this]() { io_context->run(); }).detach();

    std::cout << "Miner node started\n";
}

MiningWindow::~MiningWindow() {
    delete ui;
}
