#include "../../include/network/Peer.h"
#include <cstring>

Peer::Peer(const std::string &ip_, uint16_t port_, const unsigned char *public_key_) noexcept : ip(ip_), port(port_), last_activity(std::chrono::steady_clock::now()) {
    std::memcpy(public_key, public_key_, crypto_sign_PUBLICKEYBYTES);
}
