#include "../include/blockchain/Blockchain.h"
#include <cstring>
#include <ctime>

Blockchain::Blockchain(const unsigned char* my_address) {
    std::unordered_map<std::string, FileMetadata> files;
    auto now = std::chrono::system_clock::now();

    // Создаём генезис-блок
    Block genesis(
        my_address,          // адрес
        my_address,          // previous_address
        my_address,          // sender
        my_address,          // receiver
        now,                 // время создания
        files                // файлы
    );

    chain.push_back(genesis);
}

void Blockchain::add_block(const Block& block) {
    if (block.previous_hash != chain.back().hash()) return;
    chain.push_back(block);
}

bool Blockchain::validate_chain() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& current = chain[i];
        const Block& previous = chain[i - 1];
        if (current.previous_hash != previous.hash()) return false;
        if (!current.validate_proof_of_work()) return false;
    }
    return true;
}

const Block& Blockchain::last_block() const {
    return chain.back();
}
