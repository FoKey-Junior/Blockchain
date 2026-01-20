#include "../../include/network/CryptoUtils.h"

std::vector<uint8_t> CryptoUtils::sign_message(const std::vector<uint8_t>& msg, const unsigned char* priv_key) {
    std::vector<uint8_t> signed_msg(msg.size() + crypto_sign_BYTES);
    unsigned long long signed_len;
    crypto_sign(signed_msg.data(), &signed_len, msg.data(), msg.size(), priv_key);
    signed_msg.resize(signed_len);
    return signed_msg;
}

bool CryptoUtils::verify_message(const std::vector<uint8_t>& signed_msg, const unsigned char* pub_key, std::vector<uint8_t>& out_msg) {
    out_msg.resize(signed_msg.size());
    unsigned long long out_len;
    if (crypto_sign_open(out_msg.data(), &out_len, signed_msg.data(), signed_msg.size(), pub_key) != 0) {
        return false;
    }
    out_msg.resize(out_len);
    return true;
}