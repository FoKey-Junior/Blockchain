#ifndef BLOCKCHAIN_WALLET_H
#define BLOCKCHAIN_WALLET_H


#include <sodium.h>
#include <chrono>
#include <string>

class User {
    unsigned char public_key[crypto_sign_PUBLICKEYBYTES] = {};
    unsigned char private_key[crypto_sign_SECRETKEYBYTES] = {};
    unsigned char address_bytes[crypto_generichash_BYTES] = {};

public:
    std::string address;
    std::chrono::system_clock::time_point time_creation;

    User();
    [[nodiscard]] const unsigned char* get_private_key() const { return private_key; }
    [[nodiscard]] const unsigned char* get_public_key() const { return public_key; }
    [[nodiscard]] const unsigned char* get_address_bytes() const { return address_bytes; }
    [[nodiscard]] const std::string& get_address() const { return address; }
    void print_wallet_data() const;
    ~User();
};


#endif