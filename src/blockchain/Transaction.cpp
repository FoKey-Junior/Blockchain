#include <sodium.h>
#include <unordered_map>
#include <iostream>
#include <cstring>

#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Block.h"

Transaction::Transaction(
    const unsigned char* sender_,
    const unsigned char* receiver_,
    std::unordered_map<std::string, FileMetadata> files_
    ) : files(files_) {

    std::memcpy(this->sender, sender_, crypto_generichash_BYTES);
    std::memcpy(this->receiver, receiver_, crypto_generichash_BYTES);

    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);
    crypto_generichash_update(&state, this->sender, crypto_generichash_BYTES);
    crypto_generichash_update(&state, this->receiver, crypto_generichash_BYTES);
    crypto_generichash_final(&state, this->address, crypto_generichash_BYTES);
    time_creation = std::chrono::system_clock::now();
}

void Transaction::sign(const unsigned char* sender_private_key) {
    unsigned long long sig_len;

    if (crypto_sign_detached(signature, &sig_len, address, sizeof(address), sender_private_key) != 0) {
        throw std::runtime_error("Failed to sign transaction!");
    }
}

bool Transaction::verify(const unsigned char* sender_public_key) const {
    // Block block(address, address, sender, receiver, time_creation);
    return crypto_sign_verify_detached(signature, address, sizeof(address), sender_public_key) == 0;
}

Transaction::~Transaction() {
    sodium_memzero(sender, sizeof(sender));
    sodium_memzero(receiver, sizeof(receiver));
    sodium_memzero(address, sizeof(address));
    sodium_memzero(signature, sizeof(signature));
}
