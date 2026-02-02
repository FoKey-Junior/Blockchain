#include <catch2/catch_test_macros.hpp>
#include "../include/block.h"
#include "../include/types.h"
#include <sodium.h>
#include <vector>

TEST_CASE("block creation", "[block]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes address{};
    address_bytes previous_address{};
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    block b(address, previous_address, sender, receiver,
            std::chrono::system_clock::now(), files);
    
    REQUIRE(std::memcmp(b.get_address().data(), address.data(), address_bytes::size()) == 0);
    REQUIRE(std::memcmp(b.get_previous_address().data(), previous_address.data(), address_bytes::size()) == 0);
}

TEST_CASE("block serialization", "[block]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes address{};
    address_bytes previous_address{};
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    hash_bytes hash1{};
    files.emplace("file1", file_metadata{hash1});
    
    block b1(address, previous_address, sender, receiver,
             std::chrono::system_clock::now(), files);
    
    const std::vector<std::uint8_t> serialized = b1.serialize();
    REQUIRE_FALSE(serialized.empty());
    
    auto b2_opt = block::deserialize(serialized);
    REQUIRE(b2_opt.has_value());
    
    const block& b2 = b2_opt.value();
    REQUIRE(std::memcmp(b1.get_address().data(), b2.get_address().data(), address_bytes::size()) == 0);
    REQUIRE(std::memcmp(b1.get_previous_address().data(), b2.get_previous_address().data(), address_bytes::size()) == 0);
    REQUIRE(b1.get_files().size() == b2.get_files().size());
}

TEST_CASE("block deserialize invalid data", "[block]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    std::vector<std::uint8_t> invalid_data{1, 2, 3};
    auto block_opt = block::deserialize(invalid_data);
    REQUIRE_FALSE(block_opt.has_value());
}

TEST_CASE("block with multiple files", "[block]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes address{};
    address_bytes previous_address{};
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    for (int i = 0; i < 10; ++i) {
        hash_bytes hash{};
        files.emplace("file" + std::to_string(i), file_metadata{hash});
    }
    
    block b(address, previous_address, sender, receiver,
            std::chrono::system_clock::now(), files);
    
    REQUIRE(b.get_files().size() == 10);
    
    const std::vector<std::uint8_t> serialized = b.serialize();
    auto deserialized_opt = block::deserialize(serialized);
    REQUIRE(deserialized_opt.has_value());
    REQUIRE(deserialized_opt->get_files().size() == 10);
}

