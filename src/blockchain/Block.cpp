#include <cstring>
#include <sodium.h>
#include "../../include/blockchain/Block.h"

Block::Block(
    const unsigned char* address_,
    const unsigned char* previous_address_,
    const unsigned char* sender_,
    const unsigned char* receiver_,
    std::chrono::system_clock::time_point time_creation_,
    const std::unordered_map<std::string, FileMetadata>& files_
) : time_creation(time_creation_), files(files_) {
    std::memcpy(this->address, address_, crypto_generichash_BYTES);
    std::memcpy(this->previous_address, previous_address_, crypto_generichash_BYTES);
    std::memcpy(this->sender, sender_, crypto_generichash_BYTES);
    std::memcpy(this->receiver, receiver_, crypto_generichash_BYTES);


}
