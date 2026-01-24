#include <sodium.h>
#include <unordered_map>
#include <cstring>

#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Block.h"

Transaction::Transaction(
    const unsigned char* address_,
    const unsigned char* signature_,
    const unsigned char* sender_,
    const unsigned char* receiver_,
    std::unordered_map<std::string, FileMetadata> files_,
    std::chrono::system_clock::time_point time_
) : files(files_), time_creation(time_) {
    std::memcpy(this->address, address_, crypto_generichash_BYTES);
    std::memcpy(this->signature, signature_, crypto_sign_BYTES);
    std::memcpy(this->sender, sender_, crypto_generichash_BYTES);
    std::memcpy(this->receiver, receiver_, crypto_generichash_BYTES);
}

Transaction::Transaction(
    const unsigned char* sender_,
    const unsigned char* receiver_,
    std::unordered_map<std::string, FileMetadata> files_
    ) : files(files_) {

    std::memcpy(this->sender, sender_, crypto_generichash_BYTES);
    std::memcpy(this->receiver, receiver_, crypto_generichash_BYTES);

    crypto_generichash_state state;
    crypto_generichash_init(&state, nullptr, 0, crypto_generichash_BYTES);
    crypto_generichash_update(&state, this->sender, crypto_generichash_BYTES);
    crypto_generichash_update(&state, this->receiver, crypto_generichash_BYTES);
    crypto_generichash_final(&state, this->address, crypto_generichash_BYTES);
    time_creation = std::chrono::system_clock::now();
}

Transaction::~Transaction() {
    sodium_memzero(sender, sizeof(sender));
    sodium_memzero(receiver, sizeof(receiver));
    sodium_memzero(address, sizeof(address));
    sodium_memzero(signature, sizeof(signature));
}

void Transaction::sign_transaction(const unsigned char* sender_private_key) {
    unsigned long long sig_len;

    if (crypto_sign_detached(signature, &sig_len, address, sizeof(address), sender_private_key) != 0) {
        throw std::runtime_error("Failed to sign transaction!");
    }
}

bool Transaction::verify_transaction(const unsigned char* sender_public_key) const {
    return crypto_sign_verify_detached(signature, address, sizeof(address), sender_public_key) == 0;
}

const unsigned char * Transaction::get_address_bytes() const { return address; }
const unsigned char * Transaction::get_sender() const { return sender; }
const unsigned char * Transaction::get_receiver() const { return receiver; }
const std::unordered_map<std::string, FileMetadata>& Transaction::get_files() const { return files; }

std::vector<uint8_t> Transaction::serialize() const noexcept {
    std::vector<uint8_t> buf;
    buf.insert(buf.end(), address, address + crypto_generichash_BYTES);
    buf.insert(buf.end(), signature, signature + crypto_sign_BYTES);
    buf.insert(buf.end(), sender, sender + crypto_generichash_BYTES);
    buf.insert(buf.end(), receiver, receiver + crypto_generichash_BYTES);

    for (const auto& [name, file] : files) {
        buf.insert(buf.end(), file.content.begin(), file.content.end());
    }

    return buf;
}

std::optional<Transaction> Transaction::deserialize(const std::vector<uint8_t>& data) noexcept {
    constexpr size_t min_size = crypto_generichash_BYTES * 3 + crypto_sign_BYTES;
    if (data.size() < min_size) {
        return std::nullopt;
    }

    try {
        size_t offset = 0;
        unsigned char addr[crypto_generichash_BYTES];
        unsigned char sig[crypto_sign_BYTES];
        unsigned char send[crypto_generichash_BYTES];
        unsigned char recv[crypto_generichash_BYTES];

        std::memcpy(addr, data.data() + offset, crypto_generichash_BYTES);
        offset += crypto_generichash_BYTES;
        
        std::memcpy(sig, data.data() + offset, crypto_sign_BYTES);
        offset += crypto_sign_BYTES;
        
        std::memcpy(send, data.data() + offset, crypto_generichash_BYTES);
        offset += crypto_generichash_BYTES;
        
        std::memcpy(recv, data.data() + offset, crypto_generichash_BYTES);

        std::unordered_map<std::string, FileMetadata> files;
        auto time = std::chrono::system_clock::now();
        
        Transaction tx(addr, sig, send, recv, files, time);
        
        return tx;
    } catch (...) {
        return std::nullopt;
    }
}
