cmake_minimum_required(VERSION 4.0)
project(blockchain)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        /nix/store/l3imlvck1bdrca8ys5k12hskh6fbzsxn-crow-1.2.1.2/include
        /nix/store/zmljpwxaq8a8w9v0mm94s0qf9v9nw3m3-asio-1.24.0/include
        /nix/store/jkqv0zwpjfqz8pigppgc18gmj3pqziyw-nixos-25.11.2679.9ef261221d1e/nixos/pkgs/development/libraries/sqlite/include
        /nix/store/iwdrbfqmbxd62d50sg2ixx6lq40xm5pm-libsodium-1.0.20-dev/include
        include
)

add_executable(blockchain
        src/main.cpp
        src/api/Api.cpp
        src/core/Wallet.cpp
        include/core/Wallet.h
        src/core/Transaction.cpp
        include/core/Transaction.h
        src/core/Miner.cpp
        include/core/Miner.h
        src/core/Block.cpp
        include/core/Block.h
        src/core/Blockchain.cpp
        include/core/Blockchain.h
)

target_link_libraries(blockchain
        /nix/store/3d0pz2rax1v3b05lwjqlm4zi6dklnhs5-libsodium-1.0.20/lib/libsodium.so
        /nix/store/l30c488dws7z5mazacqsmj25izb9jlp2-sqlite-3.50.4/lib/libsqlite3.so
)
