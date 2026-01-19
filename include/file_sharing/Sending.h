#ifndef BLOCKCHAIN_SENDINGFILE_H
#define BLOCKCHAIN_SENDINGFILE_H

#include <sodium.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>

#include "../include/blockchain/User.h"
#include "../include/blockchain/Transaction.h"

class Sending {
    unsigned char sender_address[crypto_generichash_BYTES] = {};
    unsigned char receiver_address[crypto_generichash_BYTES] = {};
    std::unordered_map<std::string, FileMetadata> files;
    std::vector<std::string> file_names;
    std::vector<std::string> file_paths;
    User user;

public:
    Sending(
        const unsigned char* sender_address_,
        const unsigned char* receiver_address_,
        std::vector<std::string>&& file_names_,
        std::vector<std::string>&& file_paths_,
        const User &user_
    );
};

#endif
