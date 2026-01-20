// CryptoUtils.h
#ifndef BLOCKCHAIN_CRYPTOUTILS_H
#define BLOCKCHAIN_CRYPTOUTILS_H

#include <sodium.h>
#include <vector>

class CryptoUtils {
public:
    static std::vector<uint8_t> sign_message(const std::vector<uint8_t>& msg, const unsigned char* priv_key);
    static bool verify_message(const std::vector<uint8_t>& signed_msg, const unsigned char* pub_key, std::vector<uint8_t>& out_msg);
};

#endif
