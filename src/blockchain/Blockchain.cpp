#include <sodium.h>
#include <chrono>

#include "../../include/blockchain/Blockchain.h"

Blockchain::Blockchain(const unsigned char* my_address) {
    std::unordered_map<std::string, FileMetadata> files;
    const auto now = std::chrono::system_clock::now();

    const Block genesis(
        my_address,
        my_address,
        my_address,
        my_address,
        now,
        files
    );

    chain.push_back(genesis);
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
