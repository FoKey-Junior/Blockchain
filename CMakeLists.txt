cmake_minimum_required(VERSION 3.25)
project(Blockchain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/Users/dmitrij/Qt/6.10.1/macos/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(
        include
        include/windows
        /opt/homebrew/include
        /usr/local/include/asio
        ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)
include_directories(${SODIUM_INCLUDE_DIRS})
link_directories(${SODIUM_LIBRARY_DIRS})

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})
link_directories(${SQLite3_LIBRARY_DIRS})

set(SOURCES
        src/main.cpp
        src/windows/start_window.cpp
        src/windows/main_window.cpp

        src/api/Api.cpp
        src/core/User.cpp
        src/core/Transaction.cpp
        src/core/Miner.cpp
        src/core/Block.cpp
        src/core/Blockchain.cpp
        src/core/Mempool.cpp
        src/core/SendingFile.cpp
)

set(HEADERS
        include/windows/start_window.h
        include/windows/main_window.h
        include/api/Api.h
        include/core/User.h
        include/core/Transaction.h
        include/core/Miner.h
        include/core/Block.h
        include/core/Blockchain.h
        include/core/Mempool.h
        include/core/SendingFile.h
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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Blockchain)
endif()
