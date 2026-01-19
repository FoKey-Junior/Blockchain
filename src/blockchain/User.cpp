#include "../../include/blockchain/User.h"
#include "../../include/blockchain/Transaction.h"

User::User() {
    time_creation = std::chrono::system_clock::now();
    crypto_sign_keypair(public_key, private_key);
    crypto_generichash(address_bytes, sizeof(address_bytes), public_key, sizeof(public_key), nullptr, 0);
    std::ostringstream swap;

    for (size_t i = 0; i < sizeof(address_bytes); i++) {
        swap << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address_bytes[i]);
    }

    address = swap.str();
    print_wallet_data();
};

void User::print_wallet_data() const {
    auto print_hex = [](const unsigned char* data, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        }
    };

    const std::time_t t = std::chrono::system_clock::to_time_t(time_creation);
};

User::~User() {
    sodium_memzero(private_key, sizeof(private_key));
    sodium_memzero(public_key, sizeof(public_key));
    sodium_memzero(address_bytes, sizeof(address_bytes));
};
