#include "../include/user.h"
#include "../include/crypto_utils.h"
#include <sodium.h>
#include <sstream>
#include <iomanip>
#include <cstring>

user::user() noexcept : creation_time_(std::chrono::system_clock::now()) {
    initialize_keys();
    compute_address();
}

user::~user() noexcept {
    sodium_memzero(private_key_.data(), private_key_.size());
    sodium_memzero(public_key_.data(), public_key_.size());
    sodium_memzero(address_bytes_.data(), address_bytes_.size());
}

void user::initialize_keys() noexcept {
    crypto_sign_keypair(public_key_.data(), private_key_.data());
}

void user::compute_address() noexcept {
    crypto_utils::compute_address(public_key_, address_bytes_);
    
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');
    for (const auto byte : address_bytes_) {
        stream << std::setw(2) << static_cast<int>(byte);
    }
    address_string_ = stream.str();
}

