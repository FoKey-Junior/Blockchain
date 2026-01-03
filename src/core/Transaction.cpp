#include "../../include/core/Transaction.h"

Transaction::Transaction(
    const unsigned char* sender_data,
    const unsigned char* receiver_data,
    const uint64_t amount
    ) : amount(amount) {

    std::memcpy(sender, sender_data, crypto_generichash_BYTES);
    std::memcpy(receiver, receiver_data, crypto_generichash_BYTES);

    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);

    crypto_generichash_update(&state, sender, crypto_generichash_BYTES);
    crypto_generichash_update(&state, receiver, crypto_generichash_BYTES);
    crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(&amount),sizeof(amount));

    crypto_generichash_final(&state, address, crypto_generichash_BYTES);
}

Transaction::~Transaction() {
    sodium_memzero(sender, sizeof(sender));
    sodium_memzero(receiver, sizeof(receiver));
    sodium_memzero(address, sizeof(address));
    sodium_memzero(signature, sizeof(signature));
}
