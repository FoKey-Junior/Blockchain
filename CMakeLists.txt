cmake_minimum_required(VERSION 3.25)

# Определяем проект
project(Blockchain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверяем платформу
if(APPLE)
    message(STATUS "Configuring for macOS GUI")

    # Пути к Qt
    set(CMAKE_PREFIX_PATH "/Users/dmitrij/Qt/6.10.1/macos/lib/cmake")
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    # Qt Widgets
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

    # Заголовки и исходники GUI
    include_directories(
            include
            include/windows
            /opt/homebrew/include
            /usr/local/include
            ${CMAKE_CURRENT_BINARY_DIR}
    )

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SODIUM REQUIRED libsodium)
    include_directories(${SODIUM_INCLUDE_DIRS})
    link_directories(${SODIUM_LIBRARY_DIRS})

    find_package(SQLite3 REQUIRED)
    include_directories(${SQLite3_INCLUDE_DIRS})
    link_directories(${SQLite3_LIBRARY_DIRS})

    set(HEADERS
            include/windows/start_window.h
            include/windows/main_window.h
            include/windows/mining_window.h
            include/api/Api.h
            include/blockchain/User.h
            include/blockchain/Transaction.h
            include/blockchain/Miner.h
            include/blockchain/Block.h
            include/blockchain/Blockchain.h
            include/blockchain/Mempool.h
            include/file_sharing/sending.h
            include/network/Peer.h
            include/network/Message.h
            include/network/CryptoUtils.h
            include/network/Node.h
    )

    set(SOURCES
            src/main.cpp
            src/ui/start_window.cpp
            src/ui/main_window.cpp
            src/ui/mining_window.cpp
            src/api/Api.cpp
            src/blockchain/User.cpp
            src/blockchain/Transaction.cpp
            src/blockchain/Miner.cpp
            src/blockchain/Block.cpp
            src/blockchain/Blockchain.cpp
            src/blockchain/Mempool.cpp
            src/file_sharing/sending.cpp
            src/network/Peer.cpp
            src/network/CryptoUtils.cpp
            src/network/Node.cpp
    )

    add_executable(Blockchain
            ${SOURCES}
            ${HEADERS}
    )

    target_link_libraries(Blockchain
            PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
            ${SODIUM_LIBRARIES}
            ${SQLite3_LIBRARIES}
    )

    target_include_directories(Blockchain PRIVATE "/opt/homebrew/include")
    target_compile_definitions(Blockchain PRIVATE ASIO_STANDALONE)

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(Blockchain)
    endif()

elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux server")

    # Linux include dirs
    include_directories(
            /nix/store/l3imlvck1bdrca8ys5k12hskh6fbzsxn-crow-1.2.1.2/include
            /nix/store/zmljpwxaq8a8w9v0mm94s0qf9v9nw3m3-asio-1.24.0/include
            /nix/store/qlrwfphpz9y711mlhp2mvkwb74r8ggwc-rocksdb-10.5.1/include/rocksdb
            /nix/store/jkqv0zwpjfqz8pigppgc18gmj3pqziyw-nixos-25.11.2679.9ef261221d1e/nixos/pkgs/development/libraries/sqlite/include
            /nix/store/iwdrbfqmbxd62d50sg2ixx6lq40xm5pm-libsodium-1.0.20-dev/include
            include
    )

    set(SOURCES
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

    add_executable(server ${SOURCES})

    target_link_libraries(server
            /nix/store/3d0pz2rax1v3b05lwjqlm4zi6dklnhs5-libsodium-1.0.20/lib/libsodium.so
            /nix/store/l30c488dws7z5mazacqsmj25izb9jlp2-sqlite-3.50.4/lib/libsqlite3.so
            pthread
    )

else()
    message(FATAL_ERROR "Unsupported platform")
endif()
