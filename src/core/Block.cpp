#include "../../include/core/Block.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>

Block::Block(const unsigned char* address_data,
             const unsigned char* previous_address_data,
             const unsigned char* sender_data,
             const unsigned char* receiver_data,
             uint64_t timestamp,
             uint64_t amount)
    : timestamp(timestamp), amount(amount), nonce(0)
{
    std::memcpy(address, address_data, crypto_generichash_BYTES);
    std::memcpy(previous_address, previous_address_data, crypto_generichash_BYTES);
    std::memcpy(sender, sender_data, crypto_generichash_BYTES);
    std::memcpy(receiver, receiver_data, crypto_generichash_BYTES);
}

void Block::compute_hash(unsigned char* out_hash) const noexcept {
    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);

    crypto_generichash_update(&state, previous_address, crypto_generichash_BYTES);
    crypto_generichash_update(&state, sender, crypto_generichash_BYTES);
    crypto_generichash_update(&state, receiver, crypto_generichash_BYTES);
    crypto_generichash_update(&state, address, crypto_generichash_BYTES);
    crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(&timestamp), sizeof(timestamp));
    crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(&nonce), sizeof(nonce));
    crypto_generichash_update(&state, reinterpret_cast<const unsigned char*>(&amount), sizeof(amount));

    crypto_generichash_final(&state, out_hash, crypto_generichash_BYTES);
}

static void print_hex(const unsigned char* data, size_t size) {
    for (size_t i = 0; i < size; ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(data[i]);
    std::cout << std::dec;
}

void Block::print() const {
    std::cout << "\n==================== BLOCK ====================\n";
    std::cout << "Address:          "; print_hex(address, crypto_generichash_BYTES); std::cout << "\n";
    std::cout << "Previous address: "; print_hex(previous_address, crypto_generichash_BYTES); std::cout << "\n";
    std::cout << "Sender:           "; print_hex(sender, crypto_generichash_BYTES); std::cout << "\n";
    std::cout << "Receiver:         "; print_hex(receiver, crypto_generichash_BYTES); std::cout << "\n";
    std::cout << "Timestamp:        " << timestamp << "\n";
    std::cout << "Nonce:            " << nonce << "\n";
    std::cout << "Amount:           " << amount << "\n";
    std::cout << "===============================================\n";
}
