#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "../include/mempool.h"
#include "../include/transaction.h"
#include "../include/types.h"
#include <sodium.h>
#include <vector>
#include <thread>

TEST_CASE("mempool basic operations", "[mempool]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    mempool pool;
    
    SECTION("empty mempool") {
        REQUIRE(pool.empty());
        REQUIRE(pool.size() == 0);
        REQUIRE_FALSE(pool.pop_transaction().has_value());
    }

    SECTION("add single transaction") {
        address_bytes sender{};
        address_bytes receiver{};
        std::unordered_map<std::string, file_metadata> files;
        
        transaction tx(sender, receiver, files);
        REQUIRE(pool.add_transaction(tx));
        REQUIRE_FALSE(pool.empty());
        REQUIRE(pool.size() == 1);
    }

    SECTION("pop transaction fifo order") {
        address_bytes sender{};
        address_bytes receiver{};
        std::unordered_map<std::string, file_metadata> files;
        
        transaction tx1(sender, receiver, files);
        transaction tx2(sender, receiver, files);
        
        REQUIRE(pool.add_transaction(tx1));
        REQUIRE(pool.add_transaction(tx2));
        REQUIRE(pool.size() == 2);
        
        auto popped1 = pool.pop_transaction();
        REQUIRE(popped1.has_value());
        REQUIRE(std::memcmp(popped1->get_address().data(), tx1.get_address().data(), address_bytes::size()) == 0);
        
        auto popped2 = pool.pop_transaction();
        REQUIRE(popped2.has_value());
        REQUIRE(std::memcmp(popped2->get_address().data(), tx2.get_address().data(), address_bytes::size()) == 0);
        
        REQUIRE(pool.empty());
    }

    SECTION("duplicate transaction rejection") {
        address_bytes sender{};
        address_bytes receiver{};
        std::unordered_map<std::string, file_metadata> files;
        
        transaction tx(sender, receiver, files);
        REQUIRE(pool.add_transaction(tx));
        REQUIRE_FALSE(pool.add_transaction(tx));
        REQUIRE(pool.size() == 1);
    }

    SECTION("remove transaction") {
        address_bytes sender{};
        address_bytes receiver{};
        std::unordered_map<std::string, file_metadata> files;
        
        transaction tx(sender, receiver, files);
        REQUIRE(pool.add_transaction(tx));
        REQUIRE(pool.remove_transaction(tx.get_address()));
        REQUIRE(pool.empty());
        REQUIRE_FALSE(pool.remove_transaction(tx.get_address()));
    }

    SECTION("clear mempool") {
        address_bytes sender{};
        address_bytes receiver{};
        std::unordered_map<std::string, file_metadata> files;
        
        for (int i = 0; i < 10; ++i) {
            transaction tx(sender, receiver, files);
            pool.add_transaction(tx);
        }
        
        REQUIRE(pool.size() == 10);
        pool.clear();
        REQUIRE(pool.empty());
    }
}

TEST_CASE("mempool thread safety", "[mempool]") {
    if (sodium_init() < 0) {
        FAIL("libsodium initialization failed");
    }

    mempool pool;
    constexpr int num_threads = 4;
    constexpr int transactions_per_thread = 100;
    
    address_bytes sender{};
    address_bytes receiver{};
    std::unordered_map<std::string, file_metadata> files;

    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&pool, &sender, &receiver, &files]() {
            for (int j = 0; j < transactions_per_thread; ++j) {
                transaction tx(sender, receiver, files);
                pool.add_transaction(tx);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    REQUIRE(pool.size() == num_threads * transactions_per_thread);
    
    threads.clear();
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&pool]() {
            while (!pool.empty()) {
                pool.pop_transaction();
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    REQUIRE(pool.empty());
}

