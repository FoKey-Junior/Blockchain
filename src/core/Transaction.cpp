#include "../../include/core/Transaction.h"
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>

Transaction::Transaction(
    const unsigned char* sender_data,
    const unsigned char* receiver_data,
    uint64_t amount
) : amount(amount) {

    std::memcpy(sender, sender_data, crypto_generichash_BYTES);
    std::memcpy(receiver, receiver_data, crypto_generichash_BYTES);

    timestamp = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count()
    );

    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, sizeof(hash));
    crypto_generichash_update(&state, sender, sizeof(sender));
    crypto_generichash_update(&state, receiver, sizeof(receiver));
    crypto_generichash_update(&state,
                              reinterpret_cast<const unsigned char*>(&amount),
                              sizeof(amount));
    crypto_generichash_update(&state,
                              reinterpret_cast<const unsigned char*>(&timestamp),
                              sizeof(timestamp));
    crypto_generichash_final(&state, hash, sizeof(hash));
}

void Transaction::sign(const unsigned char* sender_private_key) {
    unsigned long long sig_len = 0;
    if (crypto_sign_detached(signature, &sig_len,
                             hash, sizeof(hash),
                             sender_private_key) != 0) {
        std::abort();
    }
}

bool Transaction::verify(const unsigned char* sender_public_key) const noexcept {
    return crypto_sign_verify_detached(
        signature, hash, sizeof(hash), sender_public_key
    ) == 0;
}

std::string Transaction::get_hash_hex() const {
    static const char* hex = "0123456789abcdef";
    std::string out;
    out.reserve(sizeof(hash) * 2);
    for (unsigned char b : hash) {
        out.push_back(hex[b >> 4]);
        out.push_back(hex[b & 0x0F]);
    }
    return out;
}

void Transaction::print() const {
    std::cout << "TX hash: " << get_hash_hex() << "\n";
}

Transaction::~Transaction() {
    sodium_memzero(sender, sizeof(sender));
    sodium_memzero(receiver, sizeof(receiver));
    sodium_memzero(hash, sizeof(hash));
    sodium_memzero(signature, sizeof(signature));
}
