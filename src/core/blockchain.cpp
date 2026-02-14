#include "core/blockchain.h"
#include "core/crypto.h"

#include <stdexcept>

namespace core {

Blockchain::Blockchain(PublicKeyBytes authority)
    : authority_(authority) {
    chain_.push_back(make_genesis());
}

Block Blockchain::make_genesis() const {
    std::vector<Transaction> transactions;
    const auto now = std::chrono::system_clock::now();
    SignatureBytes sig{};
    Block genesis(HashBytes{}, std::move(transactions), now, authority_, sig, 0);
    return genesis;
}

const Block& Blockchain::latest() const noexcept {
    return chain_.back();
}

Block Blockchain::create_block(std::vector<Transaction> transactions,
                               const PrivateKeyBytes& authority_private_key) {
    const auto previous_hash = latest().hash();
    const auto now = std::chrono::system_clock::now();
    Block unsigned_block(previous_hash, std::move(transactions), now, authority_, {}, 0);
    std::vector<std::uint8_t> signable;
    signable.reserve(256);
    signable.insert(signable.end(), unsigned_block.previous_hash().begin(), unsigned_block.previous_hash().end());
    for (const auto& tx : unsigned_block.transactions()) {
        const auto data = tx.serialize();
        signable.insert(signable.end(), data.begin(), data.end());
    }
    const auto timestamp = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());
    for (int i = 7; i >= 0; --i) {
        signable.push_back(static_cast<std::uint8_t>((timestamp >> (i * 8)) & 0xFF));
    }
    for (int i = 7; i >= 0; --i) {
        signable.push_back(static_cast<std::uint8_t>((0 >> (i * 8)) & 0xFF));
    }
    signable.insert(signable.end(), authority_.begin(), authority_.end());
    const auto signature = crypto::sign(signable, authority_private_key);
    Block signed_block(previous_hash, unsigned_block.transactions(), now, authority_, signature, 0);
    return signed_block;
}

void Blockchain::add_block(Block block) {
    chain_.push_back(std::move(block));
}

bool Blockchain::validate() const noexcept {
    if (chain_.empty()) {
        return false;
    }
    for (std::size_t i = 1; i < chain_.size(); ++i) {
        const auto& prev = chain_[i - 1];
        const auto& cur = chain_[i];
        if (cur.previous_hash() != prev.hash()) {
            return false;
        }
        if (!cur.verify_authority()) {
            return false;
        }
    }
    return true;
}

} // namespace core
