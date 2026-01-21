#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <unordered_map>
#include <chrono>
#include <string>
#include "Block.h"
#include "Transaction.h"

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain(const unsigned char* my_address);

    void add_block(const std::vector<Transaction>& transactions);
    bool validate_chain() const;
    const Block& last_block() const;
    const std::vector<Block>& get_chain() const { return chain; }
    size_t size() const { return chain.size(); }
};

#endif
