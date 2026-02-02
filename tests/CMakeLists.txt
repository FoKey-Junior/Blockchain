cmake_minimum_required(VERSION 3.25)

find_package(Catch2 3 REQUIRED)

include(Catch)
catch_discover_tests(${PROJECT_NAME}_tests)

add_executable(${PROJECT_NAME}_tests
    main.cpp
    test_mempool.cpp
    test_blockchain.cpp
    test_transaction.cpp
    test_block.cpp
    test_crypto_utils.cpp
)

target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
    ${PROJECT_NAME}_lib
    Catch2::Catch2
)

target_include_directories(${PROJECT_NAME}_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

