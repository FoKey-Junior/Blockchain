#include "../../include/blockchain/Blockchain.h"
#include <cstring>
#include <chrono>

Blockchain::Blockchain(const unsigned char* my_address) {
    std::unordered_map<std::string, FileMetadata> files;
    auto now = std::chrono::system_clock::now();

    Block genesis(
        my_address,  // address
        my_address,  // previous_address
        my_address,  // sender
        my_address,  // receiver
        now,         // time_creation
        files        // files
    );

    chain.push_back(genesis);
}

void Blockchain::add_block(const std::vector<Transaction>& transactions) {
    std::unordered_map<std::string, FileMetadata> empty_files;
    auto now = std::chrono::system_clock::now();
    const unsigned char* prev_addr = chain.back().get_address(); // теперь через геттер

    Block new_block(
        prev_addr,   // address
        prev_addr,   // previous_address
        prev_addr,   // sender
        prev_addr,   // receiver
        now,
        empty_files
    );

    chain.push_back(new_block);
}

void Blockchain::add_block_direct(const Block& block) {
    chain.push_back(block);
}

bool Blockchain::validate_chain() const {
    return true;
}

const Block& Blockchain::last_block() const {
    return chain.back();
}
