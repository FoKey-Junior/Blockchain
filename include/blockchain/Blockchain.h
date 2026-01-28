#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "Block.h"
#include "Transaction.h"

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain(const unsigned char* my_address);

    void add_block(const std::vector<Transaction>& transactions);
    void add_block_direct(const Block& block);

    static bool validate_chain();
    [[nodiscard]] const Block& last_block() const;
    [[nodiscard]] const std::vector<Block>& get_chain() const { return chain; }
    [[nodiscard]] size_t size() const { return chain.size(); }
};

#endif
