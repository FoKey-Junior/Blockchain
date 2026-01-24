#ifndef BLOCKCHAIN_MESSAGE_H
#define BLOCKCHAIN_MESSAGE_H


#include "sodium.h"
#include <cstdint>
#include <vector>
#include <array>

enum class MessageType : uint8_t {
    HELLO,
    PING,
    PONG,
    NEW_BLOCK,
    NEW_TX,
    PEER_LIST,
    TX_PROCESSED
};

struct Message {
    MessageType type;
    std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> sender_pub_key{};
    std::vector<uint8_t> payload;
};


#endif