#ifndef BLOCKCHAIN_TRANSACTION_H
#define BLOCKCHAIN_TRANSACTION_H

#include <sodium.h>
#include <iostream>
#include <cstring>

class Transaction {
public:
    unsigned char sender[crypto_generichash_BYTES] = {};
    unsigned char receiver[crypto_generichash_BYTES] = {};
    unsigned char address[crypto_generichash_BYTES] = {};
    unsigned char signature[crypto_sign_BYTES] = {};
    uint64_t amount;

    Transaction(
        const unsigned char* sender_data,
        const unsigned char* receiver_data,
        const uint64_t amount
    );

    //void sign(const unsigned char* sender_private_key);
    //void verify(const unsigned char* public_key);

    ~Transaction();
};


#endif