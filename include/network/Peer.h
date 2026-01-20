#ifndef BLOCKCHAIN_PEER_H
#define BLOCKCHAIN_PEER_H


#include <sodium.h>
#include <string>
#include <chrono>

class Peer {
    std::string ip;
    uint16_t port;

    std::chrono::steady_clock::time_point last_activity;
    unsigned char public_key[crypto_sign_PUBLICKEYBYTES] = {};

public:
    Peer(const std::string& ip_, uint16_t port_, const unsigned char* public_key_) noexcept;
    ~Peer() noexcept { clear(); }

    [[nodiscard]] std::string get_ip() const { return ip; }
    [[nodiscard]] uint16_t get_port() const { return port; }
    [[nodiscard]] std::chrono::steady_clock::time_point get_last_activity() const { return last_activity; }
    [[nodiscard]] const unsigned char* get_public_key() const { return public_key; }

    void update_last_activity() { last_activity = std::chrono::steady_clock::now(); }
    void clear() { sodium_memzero(public_key,crypto_sign_PUBLICKEYBYTES); }
};



#endif