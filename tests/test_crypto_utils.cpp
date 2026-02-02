#include <catch2/catch_test_macros.hpp>
#include "../include/crypto_utils.h"
#include "../include/user.h"
#include "../include/types.h"
#include <sodium.h>
#include <vector>

TEST_CASE("crypto_utils sign and verify message", "[crypto_utils]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    user user_instance;
    const std::vector<std::uint8_t> message{1, 2, 3, 4, 5};
    
    const std::vector<std::uint8_t> signed_message = 
        crypto_utils::sign_message(message, user_instance.get_private_key());
    
    REQUIRE_FALSE(signed_message.empty());
    
    std::vector<std::uint8_t> verified_message;
    REQUIRE(crypto_utils::verify_message(signed_message, user_instance.get_public_key(), verified_message));
    REQUIRE(verified_message == message);
}

TEST_CASE("crypto_utils compute address", "[crypto_utils]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    user user_instance;
    address_bytes computed_address{};
    
    crypto_utils::compute_address(user_instance.get_public_key(), computed_address);
    
    REQUIRE(std::memcmp(computed_address.data(), 
                       user_instance.get_address_bytes().data(), 
                       address_bytes::size()) == 0);
}

TEST_CASE("crypto_utils file hash", "[crypto_utils]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    const std::vector<std::uint8_t> file_data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    hash_bytes hash{};
    
    crypto_utils::compute_file_hash(file_data, hash);
    
    bool all_zero = true;
    for (const auto byte : hash) {
        if (byte != 0) {
            all_zero = false;
            break;
        }
    }
    REQUIRE_FALSE(all_zero);
}

TEST_CASE("crypto_utils verify file integrity", "[crypto_utils]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    const std::vector<std::uint8_t> file_data{1, 2, 3, 4, 5};
    hash_bytes hash{};
    
    crypto_utils::compute_file_hash(file_data, hash);
    REQUIRE(crypto_utils::verify_file_integrity(file_data, hash));
    
    const std::vector<std::uint8_t> modified_data{1, 2, 3, 4, 6};
    REQUIRE_FALSE(crypto_utils::verify_file_integrity(modified_data, hash));
}

TEST_CASE("crypto_utils verify invalid signature", "[crypto_utils]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    user user1;
    user user2;
    const std::vector<std::uint8_t> message{1, 2, 3};
    
    const std::vector<std::uint8_t> signed_message = 
        crypto_utils::sign_message(message, user1.get_private_key());
    
    std::vector<std::uint8_t> verified_message;
    REQUIRE_FALSE(crypto_utils::verify_message(signed_message, user2.get_public_key(), verified_message));
}

