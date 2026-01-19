#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H


#include <iostream>
#include <sodium.h>
#include <cstring>
#include <chrono>

#include <iomanip>
#include <ctime>

class Block {
    unsigned char address[crypto_generichash_BYTES] = {};
    unsigned char previous_address[crypto_generichash_BYTES] = {};

    unsigned char sender[crypto_generichash_BYTES] = {};
    unsigned char receiver[crypto_generichash_BYTES] = {};
    std::chrono::system_clock::time_point time_creation;

public:
    Block(
        const unsigned char* address_data,
        const unsigned char* previous_address_data,

        const unsigned char* sender_data,
        const unsigned char* receiver_data,
        std::chrono::system_clock::time_point time_creation
    );

    void print() const;
};


#endif