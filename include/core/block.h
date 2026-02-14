#ifndef BLOCKCHAIN_CORE_BLOCK_H
#define BLOCKCHAIN_CORE_BLOCK_H

#include "transaction.h"
#include <vector>

namespace core {

class Block {
public:
    Block(HashBytes previous_hash,
          std::vector<Transaction> transactions,
          std::chrono::system_clock::time_point created_at,
          PublicKeyBytes authority,
          SignatureBytes authority_signature,
          std::uint64_t nonce);

    HashBytes hash() const noexcept { return hash_; }
    HashBytes previous_hash() const noexcept { return previous_hash_; }
    const std::vector<Transaction>& transactions() const noexcept { return transactions_; }
    std::chrono::system_clock::time_point created_at() const noexcept { return created_at_; }
    PublicKeyBytes authority() const noexcept { return authority_; }
    SignatureBytes authority_signature() const noexcept { return authority_signature_; }
    std::uint64_t nonce() const noexcept { return nonce_; }

    std::vector<std::uint8_t> serialize() const;
    static Block deserialize(const std::vector<std::uint8_t>& data);

    bool verify_authority() const noexcept;

private:
    HashBytes hash_{};
    HashBytes previous_hash_{};
    std::vector<Transaction> transactions_{};
    std::chrono::system_clock::time_point created_at_{};
    PublicKeyBytes authority_{};
    SignatureBytes authority_signature_{};
    std::uint64_t nonce_{0};

    void compute_hash() noexcept;
};

} // namespace core

#endif
