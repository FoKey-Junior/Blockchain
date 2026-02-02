#include <catch2/catch_test_macros.hpp>
#include "../include/transaction.h"
#include "../include/user.h"
#include "../include/types.h"
#include <sodium.h>
#include <vector>

TEST_CASE("transaction creation", "[transaction]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    transaction tx(sender, receiver, files);
    
    REQUIRE(std::memcmp(tx.get_sender_address().data(), sender.data(), address_bytes::size()) == 0);
    REQUIRE(std::memcmp(tx.get_receiver_address().data(), receiver.data(), address_bytes::size()) == 0);
}

TEST_CASE("transaction signing and verification", "[transaction]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    user user_instance;
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    transaction tx(user_instance.get_address_bytes(), receiver, files);
    
    REQUIRE_NOTHROW(tx.sign(user_instance.get_private_key()));
    REQUIRE(tx.verify(user_instance.get_public_key()));
}

TEST_CASE("transaction serialization", "[transaction]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    transaction tx1(sender, receiver, files);
    const std::vector<std::uint8_t> serialized = tx1.serialize();
    REQUIRE_FALSE(serialized.empty());
    
    auto tx2_opt = transaction::deserialize(serialized);
    REQUIRE(tx2_opt.has_value());
    
    const transaction& tx2 = tx2_opt.value();
    REQUIRE(std::memcmp(tx1.get_address().data(), tx2.get_address().data(), address_bytes::size()) == 0);
    REQUIRE(std::memcmp(tx1.get_sender_address().data(), tx2.get_sender_address().data(), address_bytes::size()) == 0);
    REQUIRE(std::memcmp(tx1.get_receiver_address().data(), tx2.get_receiver_address().data(), address_bytes::size()) == 0);
}

TEST_CASE("transaction deserialize invalid data", "[transaction]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    std::vector<std::uint8_t> invalid_data{1, 2, 3};
    auto tx_opt = transaction::deserialize(invalid_data);
    REQUIRE_FALSE(tx_opt.has_value());
}

TEST_CASE("transaction with files", "[transaction]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    hash_bytes hash1{};
    hash_bytes hash2{};
    files.emplace("file1", file_metadata{hash1});
    files.emplace("file2", file_metadata{hash2});
    
    transaction tx(sender, receiver, files);
    REQUIRE(tx.get_files().size() == 2);
    REQUIRE(tx.get_files().count("file1") == 1);
    REQUIRE(tx.get_files().count("file2") == 1);
}

