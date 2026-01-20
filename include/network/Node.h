#ifndef NODE_H
#define NODE_H

#include "../blockchain/Transaction.h"
#include "../blockchain/Blockchain.h"
#include "../blockchain/Miner.h"
#include <vector>
#include <asio.hpp>

class Node {
private:
    std::vector<Transaction>* mempool = nullptr;
    Blockchain* blockchain = nullptr;
    Miner* miner = nullptr;

public:
    Node(asio::io_context& io, uint16_t port, const unsigned char* pub_key, const unsigned char* priv_key) {
        // инициализация сокета и ключей
    }

    void set_mempool(std::vector<Transaction>* m) { mempool = m; }
    void set_blockchain(Blockchain* bc) { blockchain = bc; }
    void set_miner(Miner* m) { miner = m; }

    void start() {

    }
};

#endif
