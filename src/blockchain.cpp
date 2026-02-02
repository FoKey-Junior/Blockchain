#include "../include/blockchain.h"
#include <sodium.h>
#include <cstring>
#include <algorithm>

block blockchain::make_genesis_block() noexcept {
    constexpr const char* genesis_seed = "BlockchainGenesisBlock";
    address_bytes genesis_address;
    crypto_generichash(genesis_address.data(), genesis_address.size(),
                       reinterpret_cast<const unsigned char*>(genesis_seed),
                       std::strlen(genesis_seed),
                       nullptr, 0);

    address_bytes zeros{};
    std::unordered_map<std::string, file_metadata> files;
    const auto epoch_zero = std::chrono::system_clock::from_time_t(0);

    return block(genesis_address, genesis_address, zeros, zeros, epoch_zero, files);
}

blockchain::blockchain(const address_bytes& /* miner_address */) noexcept {
    chain_.push_back(make_genesis_block());
}

void blockchain::add_block(const std::vector<transaction>& transactions) noexcept {
    if (transactions.empty()) {
        return;
    }

    const auto now = std::chrono::system_clock::now();
    const address_bytes& previous_address = chain_.back().get_address();

    std::unordered_map<std::string, file_metadata> files;
    for (const auto& tx : transactions) {
        const auto& tx_files = tx.get_files();
        files.insert(tx_files.begin(), tx_files.end());
    }

    address_bytes block_address;
    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);
    crypto_generichash_update(&state, previous_address.data(), previous_address.size());
    for (const auto& tx : transactions) {
        crypto_generichash_update(&state, tx.get_address().data(), tx.get_address().size());
    }
    crypto_generichash_final(&state, block_address.data(), block_address.size());

    const address_bytes& sender_address = transactions.front().get_sender_address();
    const address_bytes& receiver_address = transactions.front().get_receiver_address();

    block new_block(block_address, previous_address, sender_address, receiver_address, now, files);
    chain_.push_back(new_block);
}

void blockchain::add_block_direct(const block& block_to_add) noexcept {
    chain_.push_back(block_to_add);
}

bool blockchain::validate_chain() const noexcept {
    if (chain_.empty()) {
        return false;
    }

    for (std::size_t i = 1; i < chain_.size(); ++i) {
        const address_bytes& current_previous = chain_[i].get_previous_address();
        const address_bytes& previous_address = chain_[i - 1].get_address();

        if (std::memcmp(current_previous.data(), previous_address.data(), crypto_generichash_BYTES) != 0) {
            return false;
        }
    }

    return true;
}

const block& blockchain::get_last_block() const noexcept {
    return chain_.back();
}

