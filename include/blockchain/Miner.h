#ifndef MINER_H
#define MINER_H

#include "Transaction.h"
#include "Blockchain.h"
#include <vector>
#include <mutex>

// Forward declaration
class Node;

class Miner {
private:
    std::vector<Transaction>& mempool;
    Blockchain* blockchain = nullptr;
    std::mutex* mempool_mutex_ptr = nullptr; // Указатель на мьютекс из Node
    Node* node_ptr = nullptr; // Указатель на Node для рассылки блоков

public:
    explicit Miner(std::vector<Transaction>& mempool_);

    void set_blockchain(Blockchain* bc) { blockchain = bc; }
    void set_mempool_mutex(std::mutex* mutex_ptr) { mempool_mutex_ptr = mutex_ptr; }
    void set_node(Node* node) { node_ptr = node; }

    void start_mining();
};

#endif
