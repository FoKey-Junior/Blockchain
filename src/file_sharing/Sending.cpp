#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "../../include/file_sharing/Sending.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Mempool.h"

Mempool mempool;

Sending::Sending(
    const unsigned char* sender_address_,
    const unsigned char* receiver_address_,
    std::vector<std::string>&& file_names_,
    std::vector<std::string>&& file_paths_,
    const User &user_
    ) :
    file_names(std::move(file_names_)),
    file_paths(std::move(file_paths_)),
    user(user_)
{
    std::memcpy(sender_address, sender_address_, crypto_generichash_BYTES);
    std::memcpy(receiver_address, receiver_address_, crypto_generichash_BYTES);

    std::vector<unsigned char> buffer(4096);
    std::array<unsigned char, crypto_hash_sha256_BYTES> name_hash{};
    char name_hash_hex[crypto_hash_sha256_BYTES * 2 + 1]{};

    if (file_names.size() != file_paths.size()) {
        throw std::logic_error("file_names and file_paths size mismatch");
    }

    for (size_t i = 0; i < file_paths.size(); ++i) {
        const std::string& file_path = file_paths[i];
        const std::string& file_name = file_names[i];

        crypto_hash_sha256(
            name_hash.data(),
            reinterpret_cast<const unsigned char*>(file_name.data()),
            file_name.size()
        );

        sodium_bin2hex(
            name_hash_hex,
            sizeof(name_hash_hex),
            name_hash.data(),
            crypto_hash_sha256_BYTES
        );

        std::string name_hash_str{name_hash_hex};

        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }

        std::array<unsigned char, crypto_hash_sha256_BYTES> content_hash{};
        crypto_hash_sha256_state state;
        crypto_hash_sha256_init(&state);

        while (file.good()) {
            file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            const std::streamsize read_bytes = file.gcount();

            if (read_bytes > 0) {
                crypto_hash_sha256_update(
                    &state,
                    buffer.data(),
                    static_cast<size_t>(read_bytes)
                );
            }
        }

        crypto_hash_sha256_final(&state, content_hash.data());
        files.emplace(name_hash_str, FileMetadata{content_hash});
    }

    Transaction transaction(sender_address, receiver_address, files);
    transaction.sign(user.get_private_key());

    if (transaction.verify(user.get_public_key())) {
        mempool.add_transaction(transaction);
    }
}
