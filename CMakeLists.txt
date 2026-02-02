cmake_minimum_required(VERSION 3.25)

project(Blockchain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SODIUM libsodium)
if(SODIUM_FOUND)
    message(STATUS "Found libsodium via pkg-config")
    message(STATUS "  Libraries: ${SODIUM_LIBRARIES}")
    message(STATUS "  Library dirs: ${SODIUM_LIBRARY_DIRS}")
    message(STATUS "  Include dirs: ${SODIUM_INCLUDE_DIRS}")
    if(SODIUM_LIBRARY_DIRS)
        link_directories(${SODIUM_LIBRARY_DIRS})
    endif()
else()
    message(STATUS "libsodium not found via pkg-config, searching manually...")
    find_library(SODIUM_LIB_FOUND 
        NAMES sodium libsodium
        PATHS 
            /opt/homebrew/lib
            /usr/local/lib
            /usr/lib
    )
    find_path(SODIUM_INCLUDE_FOUND 
        NAMES sodium.h
        PATHS 
            /opt/homebrew/include
            /usr/local/include
            /usr/include
    )
    if(SODIUM_LIB_FOUND AND SODIUM_INCLUDE_FOUND)
        set(SODIUM_LIBRARIES ${SODIUM_LIB_FOUND})
        set(SODIUM_INCLUDE_DIRS ${SODIUM_INCLUDE_FOUND})
        get_filename_component(SODIUM_LIBRARY_DIRS ${SODIUM_LIB_FOUND} DIRECTORY)
        link_directories(${SODIUM_LIBRARY_DIRS})
        message(STATUS "Found libsodium manually: ${SODIUM_LIBRARIES}")
        set(SODIUM_FOUND TRUE)
    else()
        message(FATAL_ERROR "libsodium not found! Please install it:\n"
            "  macOS: brew install libsodium\n"
            "  Linux: apt-get install libsodium-dev")
    endif()
endif()

find_path(ASIO_INCLUDE_DIR asio.hpp
    PATHS
        $ENV{ASIO_ROOT}/include
        /usr/include
        /usr/local/include
        /opt/homebrew/include
        ${CMAKE_SOURCE_DIR}/third_party/asio/include
)

if(ASIO_INCLUDE_DIR)
    message(STATUS "Found ASIO at: ${ASIO_INCLUDE_DIR}")
else()
    find_path(ASIO_INCLUDE_DIR asio.hpp
        PATHS
            /opt/homebrew/include
            /usr/local/include
            /usr/include
    )
endif()

set(COMMON_HEADERS
    include/types.h
    include/message_type.h
    include/crypto_utils.h
    include/user.h
    include/transaction.h
    include/block.h
    include/blockchain.h
    include/mempool.h
    include/miner.h
    include/file_sender.h
    include/message.h
    include/peer.h
    include/node.h
    include/port_utils.h
)

set(COMMON_SOURCES
    src/crypto_utils.cpp
    src/user.cpp
    src/transaction.cpp
    src/block.cpp
    src/blockchain.cpp
    src/mempool.cpp
    src/miner.cpp
    src/file_sender.cpp
    src/peer.cpp
    src/node.cpp
    src/port_utils.cpp
)

list(APPEND COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SODIUM_INCLUDE_DIRS}
    ${PLATFORM_INCLUDE_DIRS}
)

if(ASIO_INCLUDE_DIR)
    list(APPEND COMMON_INCLUDE_DIRS ${ASIO_INCLUDE_DIR})
endif()

add_library(${PROJECT_NAME}_lib STATIC
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

target_include_directories(${PROJECT_NAME}_lib
    PRIVATE ${COMMON_INCLUDE_DIRS}
)

target_compile_definitions(${PROJECT_NAME}_lib
    PRIVATE ASIO_STANDALONE
)

target_link_libraries(${PROJECT_NAME}_lib
    PRIVATE 
    ${SODIUM_LIBRARIES}
    pthread
)

if(APPLE AND SODIUM_LIBRARY_DIRS)
    target_link_directories(${PROJECT_NAME}_lib PRIVATE ${SODIUM_LIBRARY_DIRS})
endif()

if(UNIX AND NOT APPLE)
    add_executable(server src/main_server.cpp)
    
    target_include_directories(server PRIVATE ${COMMON_INCLUDE_DIRS})
    target_compile_definitions(server PRIVATE ASIO_STANDALONE)
    
    target_link_libraries(server
        PRIVATE
        ${PROJECT_NAME}_lib
        ${SODIUM_LIBRARIES}
        pthread
    )
endif()

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    find_package(Catch2 3 QUIET)
    if(Catch2_FOUND)
        list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
        include(Catch)
        
        add_executable(${PROJECT_NAME}_tests
            tests/main.cpp
            tests/test_mempool.cpp
            tests/test_blockchain.cpp
            tests/test_transaction.cpp
            tests/test_block.cpp
            tests/test_crypto_utils.cpp
        )
        
        target_link_libraries(${PROJECT_NAME}_tests
            PRIVATE
            ${PROJECT_NAME}_lib
            Catch2::Catch2
        )
        
        target_include_directories(${PROJECT_NAME}_tests
            PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
        
        catch_discover_tests(${PROJECT_NAME}_tests)
    else()
        message(STATUS "Catch2 not found, skipping tests")
    endif()
endif()
