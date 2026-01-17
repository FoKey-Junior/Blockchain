cmake_minimum_required(VERSION 3.25)
project(blockchain)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)
include_directories(${SODIUM_INCLUDE_DIRS})
link_directories(${SODIUM_LIBRARY_DIRS})

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})
link_directories(${SQLite3_LIBRARY_DIRS})

include_directories(/opt/homebrew/include)
include_directories(/usr/local/include/asio)

add_executable(blockchain
        src/main.cpp
        src/api/Api.cpp
        src/core/User.cpp
        src/core/Transaction.cpp
        src/core/Miner.cpp
        src/core/Block.cpp
        src/core/Blockchain.cpp
        src/core/Mempool.cpp
)

target_link_libraries(blockchain
        ${SODIUM_LIBRARIES}
        ${SQLite3_LIBRARIES}
)
