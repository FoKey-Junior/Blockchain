#ifndef MESSAGE_H
#define MESSAGE_H

#include "message_type.h"
#include "types.h"
#include <vector>
#include <cstdint>

struct message {
    message_type type;
    public_key_bytes sender_public_key;
    std::vector<std::uint8_t> payload;
};

#endif

