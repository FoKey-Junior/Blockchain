#ifndef BLOCKCHAIN_WALLET_H
#define BLOCKCHAIN_WALLET_H


#include <sodium.h>
#include <iostream>
#include <chrono>
#include <string>

class Wallet {
    unsigned char public_key[crypto_sign_PUBLICKEYBYTES] = {};
    unsigned char private_key[crypto_sign_SECRETKEYBYTES] = {};
    unsigned char address_bytes[crypto_generichash_BYTES] = {};

public:
    std::string address;
    std::chrono::system_clock::time_point time_creation;
    uint64_t balance = 1000;

    Wallet();
    const unsigned char* get_private_key() const { return private_key; }
    const unsigned char* get_public_key() const { return public_key; }
    const unsigned char* get_address_bytes() const { return address_bytes; }
    const std::string& get_address() const { return address; }
    void print_wallet_data() const;
    ~Wallet();
};


#endif