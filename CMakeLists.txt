cmake_minimum_required(VERSION 4.0)
project(blockchain_server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include dirs
include_directories(
    /nix/store/l3imlvck1bdrca8ys5k12hskh6fbzsxn-crow-1.2.1.2/include
    /nix/store/zmljpwxaq8a8w9v0mm94s0qf9v9nw3m3-asio-1.24.0/include
    /nix/store/qlrwfphpz9y711mlhp2mvkwb74r8ggwc-rocksdb-10.5.1/include/rocksdb
    /nix/store/jkqv0zwpjfqz8pigppgc18gmj3pqziyw-nixos-25.11.2679.9ef261221d1e/nixos/pkgs/development/libraries/sqlite/include
    /nix/store/iwdrbfqmbxd62d50sg2ixx6lq40xm5pm-libsodium-1.0.20-dev/include
    include
)

# All source files
add_executable(server
    src/main_server.cpp

    src/blockchain/Block.cpp
    src/blockchain/Blockchain.cpp
    src/blockchain/Transaction.cpp
    src/blockchain/User.cpp
    src/blockchain/Miner.cpp

    src/network/Node.cpp
    src/network/Peer.cpp
    src/network/CryptoUtils.cpp
)

# Link libraries
target_link_libraries(server
    /nix/store/3d0pz2rax1v3b05lwjqlm4zi6dklnhs5-libsodium-1.0.20/lib/libsodium.so
    /nix/store/l30c488dws7z5mazacqsmj25izb9jlp2-sqlite-3.50.4/lib/libsqlite3.so
    pthread
)

