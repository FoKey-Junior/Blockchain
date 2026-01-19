#include "../../include/file_sharing/Sending.h"

Sending::Sending(
    const unsigned char* sender_address_,
    const unsigned char* receiver_address_,
    std::vector<std::string>&& file_names_,
    std::vector<std::string>&& file_paths_
    ) : file_names(std::move(file_names_)), file_paths(std::move(file_paths_)) {

    std::memcpy(this->sender_address, sender_address_, crypto_generichash_BYTES);
    std::memcpy(this->receiver_address, receiver_address_ ,crypto_generichash_BYTES);


}
