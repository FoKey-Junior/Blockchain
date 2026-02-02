#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "transaction.h"
#include <vector>
#include <cstddef>

class blockchain {
private:
    std::vector<block> chain_;

    static block make_genesis_block() noexcept;

public:
    explicit blockchain(const address_bytes& miner_address) noexcept;
    ~blockchain() = default;

    blockchain(const blockchain&) = delete;
    blockchain& operator=(const blockchain&) = delete;
    blockchain(blockchain&&) noexcept = default;
    blockchain& operator=(blockchain&&) noexcept = default;

    void add_block(const std::vector<transaction>& transactions) noexcept;
    void add_block_direct(const block& block_to_add) noexcept;

    [[nodiscard]] bool validate_chain() const noexcept;
    [[nodiscard]] const block& get_last_block() const noexcept;
    [[nodiscard]] const std::vector<block>& get_chain() const noexcept { return chain_; }
    [[nodiscard]] std::size_t size() const noexcept { return chain_.size(); }
    [[nodiscard]] bool empty() const noexcept { return chain_.empty(); }
};

#endif

