#ifndef BLOCKCHAIN_WALLET_H
#define BLOCKCHAIN_WALLET_H

#include <sodium.h>
#include <iostream>
#include <chrono>
#include <string>

class Wallet {
    unsigned char public_key[crypto_box_PUBLICKEYBYTES] = {};
    unsigned char private_key[crypto_box_SECRETKEYBYTES] = {};
    unsigned char address_bytes[crypto_generichash_BYTES] = {};

public:
    std::string address;
    std::chrono::system_clock::time_point time_creation;
    uint64_t balance = 1000;

    Wallet();
    void print_wallet_data() const;
    ~Wallet();
};


#endif