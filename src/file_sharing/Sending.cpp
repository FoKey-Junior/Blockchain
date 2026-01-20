#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

#include "../../include/file_sharing/Sending.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Mempool.h"

Sending::Sending(
    const unsigned char* sender_address_,
    const unsigned char* receiver_address_,
    std::vector<std::string>&& file_names_,
    std::vector<std::string>&& file_paths_,
    const User &user_,
    Node &node_
) : file_names(std::move(file_names_)),
    file_paths(std::move(file_paths_)),
    user(user_),
    node(node_)
{
    std::memcpy(sender_address, sender_address_, crypto_generichash_BYTES);
    std::memcpy(receiver_address, receiver_address_, crypto_generichash_BYTES);
}

void Sending::prepare_and_send() {
    if (file_names.size() != file_paths.size()) {
        throw std::logic_error("file_names and file_paths size mismatch");
    }

    std::vector<unsigned char> buffer(4096);
    std::array<unsigned char, crypto_hash_sha256_BYTES> name_hash{};
    char name_hash_hex[crypto_hash_sha256_BYTES * 2 + 1]{};

    for (size_t i = 0; i < file_paths.size(); ++i) {
        const std::string& file_path = file_paths[i];
        const std::string& file_name = file_names[i];

        // Хэш имени файла
        crypto_hash_sha256(name_hash.data(),
                           reinterpret_cast<const unsigned char*>(file_name.data()),
                           file_name.size());

        sodium_bin2hex(name_hash_hex, sizeof(name_hash_hex),
                       name_hash.data(), crypto_hash_sha256_BYTES);

        std::string name_hash_str{name_hash_hex};

        // Хэш содержимого файла
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) throw std::runtime_error("Cannot open file: " + file_path);

        std::array<unsigned char, crypto_hash_sha256_BYTES> content_hash{};
        crypto_hash_sha256_state state;
        crypto_hash_sha256_init(&state);

        while (file.good()) {
            file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
            std::streamsize read_bytes = file.gcount();
            if (read_bytes > 0)
                crypto_hash_sha256_update(&state, buffer.data(), static_cast<size_t>(read_bytes));
        }
        crypto_hash_sha256_final(&state, content_hash.data());

        files.emplace(name_hash_str, FileMetadata{content_hash});
    }

    // Создаем транзакцию
    Transaction transaction(sender_address, receiver_address, files);
    transaction.sign_transaction(user.get_private_key());

    if (transaction.verify_transaction(user.get_public_key())) {
        std::vector<uint8_t> tx_bytes = transaction.serialize();
        node.add_transaction(tx_bytes); // Отправка через Node
    }
}
