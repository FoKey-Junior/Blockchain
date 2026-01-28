#ifndef BLOCKCHAIN_CRYPTO_UTILS_H
#define BLOCKCHAIN_CRYPTO_UTILS_H

#include <vector>

class CryptoUtils {
public:
    static std::vector<uint8_t> sign_message(const std::vector<uint8_t>& msg, const unsigned char* private_key);
    static bool verify_message(const std::vector<uint8_t>& signed_msg, const unsigned char* public_key, std::vector<uint8_t>& out_msg);
};

#endif
