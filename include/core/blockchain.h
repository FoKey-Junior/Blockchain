#ifndef BLOCKCHAIN_CORE_BLOCKCHAIN_H
#define BLOCKCHAIN_CORE_BLOCKCHAIN_H

#include "block.h"
#include <vector>

namespace core {

class Blockchain {
public:
    explicit Blockchain(PublicKeyBytes authority);

    void add_block(Block block);
    Block create_block(std::vector<Transaction> transactions,
                       const PrivateKeyBytes& authority_private_key);

    bool validate() const noexcept;
    const std::vector<Block>& chain() const noexcept { return chain_; }
    const Block& latest() const noexcept;

private:
    std::vector<Block> chain_;
    PublicKeyBytes authority_;

    Block make_genesis() const;
};

} // namespace core

#endif
