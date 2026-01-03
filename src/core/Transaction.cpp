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

void Transaction::sign(const unsigned char* sender_private_key) {
    unsigned long long sig_len;

    if (crypto_sign_detached(signature, &sig_len, address, sizeof(address), sender_private_key) != 0) {
        throw std::runtime_error("Failed to sign transaction!");
    }
};

bool Transaction::verify(const unsigned char* sender_public_key) const {
    return crypto_sign_verify_detached(signature, address, sizeof(address), sender_public_key) == 0;
}

void Transaction::print() const {
    auto print_hex = [](const unsigned char* data, size_t len) {
        for (size_t i = 0; i < len; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(data[i]);
        }
    };

    std::cout << "Sender:   ";   print_hex(sender, sizeof(sender));   std::cout << "\n";
    std::cout << "Receiver: ";   print_hex(receiver, sizeof(receiver)); std::cout << "\n";
    std::cout << "Amount:   " << amount << "\n";
    std::cout << "Tx hash:  ";   print_hex(address, sizeof(address));  std::cout << "\n";
    std::cout << "Signature:";    print_hex(signature, sizeof(signature)); std::cout << "\n";
}

Transaction::~Transaction() {
    sodium_memzero(sender, sizeof(sender));
    sodium_memzero(receiver, sizeof(receiver));
    sodium_memzero(address, sizeof(address));
    sodium_memzero(signature, sizeof(signature));
}
