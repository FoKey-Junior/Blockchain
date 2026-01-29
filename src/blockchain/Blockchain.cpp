#include <sodium.h>
#include <chrono>
#include <cstring>

#include "../../include/blockchain/Blockchain.h"

namespace {
// Фиксированный genesis для всей сети — один и тот же на сервере и всех клиентах,
// иначе блоки с сервера отклоняются («previous address doesn't match»).
Block make_genesis_block() {
    const char* genesis_seed = "BlockchainGenesisBlock";
    unsigned char genesis_address[crypto_generichash_BYTES];
    crypto_generichash(genesis_address, sizeof(genesis_address),
                       reinterpret_cast<const unsigned char*>(genesis_seed),
                       static_cast<std::size_t>(std::strlen(genesis_seed)),
                       nullptr, 0);

    unsigned char zeros[crypto_generichash_BYTES] = {};

    std::unordered_map<std::string, FileMetadata> files;
    const auto epoch_zero = std::chrono::system_clock::from_time_t(0);

    return Block(
        genesis_address,
        genesis_address,
        zeros,
        zeros,
        epoch_zero,
        files
    );
}
}

Blockchain::Blockchain(const unsigned char* /* my_address */) {
    chain.push_back(make_genesis_block());
}

void Blockchain::add_block(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        return;
    }
    
    auto now = std::chrono::system_clock::now();
    const unsigned char* prev_addr = chain.back().get_address();
    
    std::unordered_map<std::string, FileMetadata> files;
    for (const auto& tx : transactions) {
        const auto& tx_files = tx.get_files();
        files.insert(tx_files.begin(), tx_files.end());
    }
    
    unsigned char block_address[crypto_generichash_BYTES];
    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);
    crypto_generichash_update(&state, prev_addr, crypto_generichash_BYTES);
    for (const auto& tx : transactions) {
        const unsigned char* tx_addr = tx.get_address_bytes();
        crypto_generichash_update(&state, tx_addr, crypto_generichash_BYTES);
    }
    crypto_generichash_final(&state, block_address, crypto_generichash_BYTES);
    
    const unsigned char* sender_addr = transactions[0].get_sender();
    const unsigned char* receiver_addr = transactions[0].get_receiver();
    
    Block new_block(
        block_address,
        prev_addr,
        sender_addr,
        receiver_addr,
        now,
        files
    );

    chain.push_back(new_block);
}

void Blockchain::add_block_direct(const Block& block) {
    chain.push_back(block);
}

bool Blockchain::validate_chain() {
    return true;
}

const Block& Blockchain::last_block() const {
    return chain.back();
}
