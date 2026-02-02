#include <catch2/catch_test_macros.hpp>
#include "../include/blockchain.h"
#include "../include/transaction.h"
#include "../include/types.h"
#include <sodium.h>
#include <vector>

TEST_CASE("blockchain initialization", "[blockchain]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes miner_address{};
    blockchain chain(miner_address);
    
    REQUIRE_FALSE(chain.empty());
    REQUIRE(chain.size() == 1);
}

TEST_CASE("blockchain add block", "[blockchain]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes miner_address{};
    blockchain chain(miner_address);
    
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    std::vector<transaction> transactions;
    for (int i = 0; i < 5; ++i) {
        transactions.emplace_back(sender, receiver, files);
    }
    
    chain.add_block(transactions);
    REQUIRE(chain.size() == 2);
    
    const block& last = chain.get_last_block();
    REQUIRE(std::memcmp(last.get_sender_address().data(), sender.data(), address_bytes::size()) == 0);
}

TEST_CASE("blockchain validation", "[blockchain]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes miner_address{};
    blockchain chain(miner_address);
    
    REQUIRE(chain.validate_chain());
    
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    std::vector<transaction> transactions;
    transactions.emplace_back(sender, receiver, files);
    
    chain.add_block(transactions);
    REQUIRE(chain.validate_chain());
}

TEST_CASE("blockchain empty transactions", "[blockchain]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes miner_address{};
    blockchain chain(miner_address);
    const std::size_t initial_size = chain.size();
    
    std::vector<transaction> empty_transactions;
    chain.add_block(empty_transactions);
    
    REQUIRE(chain.size() == initial_size);
}

TEST_CASE("blockchain add block direct", "[blockchain]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    address_bytes miner_address{};
    blockchain chain(miner_address);
    
    address_bytes address{};
    address_bytes previous_address = chain.get_last_block().get_address();
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;
    
    block new_block(address, previous_address, sender, receiver,
                   std::chrono::system_clock::now(), files);
    
    chain.add_block_direct(new_block);
    REQUIRE(chain.size() == 2);
}

