#include "../include/file_sender.h"
#include "../include/node.h"
#include "../include/crypto_utils.h"
#include <fstream>
#include <sstream>
#include <sodium.h>
#include <stdexcept>
#include <algorithm>

file_sender::file_sender(
    const address_bytes& sender_address,
    const address_bytes& receiver_address,
    std::vector<std::string> file_names,
    std::vector<std::string> file_paths,
    const user& user_ref,
    node& node_ref
) noexcept : sender_address_(sender_address),
             receiver_address_(receiver_address),
             file_names_(std::move(file_names)),
             file_paths_(std::move(file_paths)),
             user_ref_(user_ref),
             node_ref_(node_ref) {
}

std::unordered_map<std::string, file_metadata> file_sender::prepare_files() const noexcept(false) {
    if (file_names_.size() != file_paths_.size()) {
        throw std::logic_error("File names and paths count mismatch");
    }

    std::unordered_map<std::string, file_metadata> files;
    constexpr std::size_t buffer_size = 4096;
    std::vector<std::uint8_t> buffer(buffer_size);

    for (std::size_t i = 0; i < file_paths_.size(); ++i) {
        const std::string& file_path = file_paths_[i];
        const std::string& file_name = file_names_[i];

        hash_bytes name_hash;
        crypto_hash_sha256(name_hash.data(),
                          reinterpret_cast<const unsigned char*>(file_name.data()),
                          file_name.size());

        char name_hash_hex[crypto_hash_sha256_BYTES * 2 + 1]{};
        sodium_bin2hex(name_hash_hex, sizeof(name_hash_hex),
                      name_hash.data(), crypto_hash_sha256_BYTES);

        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }

        hash_bytes content_hash;
        crypto_hash_sha256_state state;
        crypto_hash_sha256_init(&state);

        while (file.good()) {
            file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            const std::streamsize read_bytes = file.gcount();
            if (read_bytes > 0) {
                crypto_hash_sha256_update(&state, buffer.data(), static_cast<std::size_t>(read_bytes));
            }
        }

        crypto_hash_sha256_final(&state, content_hash.data());

        files.emplace(std::string(name_hash_hex), file_metadata{content_hash});
    }

    return files;
}

void file_sender::prepare_and_send() noexcept(false) {
    auto files = prepare_files();

    transaction tx(sender_address_, receiver_address_, std::move(files));
    tx.sign(user_ref_.get_private_key());

    if (!tx.verify(user_ref_.get_public_key())) {
        throw std::runtime_error("Transaction verification failed after signing");
    }

    const std::vector<std::uint8_t> tx_bytes = tx.serialize();
    node_ref_.add_transaction(tx_bytes);
}

