#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

#include <cstdint>

enum class message_type : std::uint8_t {
    hello = 0,
    ping = 1,
    pong = 2,
    new_block = 3,
    new_transaction = 4,
    peer_list = 5,
    transaction_processed = 6
};

#endif

