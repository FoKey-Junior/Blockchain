cmake_minimum_required(VERSION 3.25)
project(Blockchain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Qt (для GUI) ---
set(CMAKE_PREFIX_PATH "/Users/dmitrij/Qt/6.10.1/macos/lib/cmake")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# --- Общие include dirs ---
include_directories(
        include
        include/windows
        /opt/homebrew/include
        /usr/local/include
)

# --- libsodium ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)
include_directories(${SODIUM_INCLUDE_DIRS})
link_directories(${SODIUM_LIBRARY_DIRS})

# --- SQLite ---
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})
link_directories(${SQLite3_LIBRARY_DIRS})

# --- Источники ---
set(BLOCKCHAIN_SOURCES
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

set(BLOCKCHAIN_HEADERS
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
# === GUI цель (Mac) ===
if(APPLE)
    set(GUI_SOURCES
            src/ui/start_window.cpp
            src/ui/main_window.cpp
            src/ui/mining_window.cpp
            src/main.cpp
    )

    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    add_executable(Blockchain   # <- теперь дефолтное имя
            ${BLOCKCHAIN_SOURCES}
            ${BLOCKCHAIN_HEADERS}
            ${GUI_SOURCES}
    )

    target_link_libraries(Blockchain
            PRIVATE Qt6::Widgets
            ${SODIUM_LIBRARIES}
            ${SQLite3_LIBRARIES}
    )

    target_compile_definitions(Blockchain PRIVATE ASIO_STANDALONE)
    target_include_directories(Blockchain PRIVATE "/opt/homebrew/include")

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(Blockchain)
    endif()
endif()

# === Серверная цель (Linux) ===
if(UNIX AND NOT APPLE)
    add_executable(BlockchainServer
            ${BLOCKCHAIN_SOURCES}
            ${BLOCKCHAIN_HEADERS}
            src/main_server.cpp
    )

    find_package(Threads REQUIRED)

    target_link_libraries(BlockchainServer
            PRIVATE Threads::Threads
            ${SODIUM_LIBRARIES}
            ${SQLite3_LIBRARIES}
    )

    target_compile_definitions(BlockchainServer PRIVATE ASIO_STANDALONE)
    target_include_directories(BlockchainServer PRIVATE "/usr/include")
endif()