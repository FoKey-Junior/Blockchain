#include "../include/peer.h"
#include <sodium.h>
#include <cstring>

peer::peer(const std::string& ip_address, std::uint16_t port, const public_key_bytes& public_key) noexcept
    : ip_address_(ip_address),
      port_(port),
      last_activity_(std::chrono::steady_clock::now()),
      public_key_(public_key) {
}

peer::~peer() noexcept {
    sodium_memzero(public_key_.data(), public_key_.size());
}

