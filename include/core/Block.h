#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <array>
#include <vector>
#include <memory>
#include <sodium.h>
#include "Transaction.h"

class Block {
public:
    unsigned char address[crypto_generichash_BYTES]{};
    unsigned char previous_address[crypto_generichash_BYTES]{};
    unsigned char sender[crypto_generichash_BYTES]{};
    unsigned char receiver[crypto_generichash_BYTES]{};

    uint64_t timestamp{};
    uint64_t nonce{};
    uint64_t amount{};

    Block(const unsigned char* address_data,
          const unsigned char* previous_address_data,
          const unsigned char* sender_data,
          const unsigned char* receiver_data,
          uint64_t timestamp,
          uint64_t amount);

    void compute_hash(unsigned char* out_hash) const noexcept;
    void print() const;
};

#endif
