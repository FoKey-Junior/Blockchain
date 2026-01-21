cmake_minimum_required(VERSION 3.25)

# Определяем проект
project(Blockchain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Общие настройки для всех платформ
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Поиск зависимостей (работает на всех платформах)
find_package(PkgConfig REQUIRED)

# libsodium
pkg_check_modules(SODIUM REQUIRED libsodium)
if(NOT SODIUM_FOUND)
    # Fallback: пробуем найти через find_package
    find_library(SODIUM_LIBRARIES NAMES sodium)
    find_path(SODIUM_INCLUDE_DIRS NAMES sodium.h PATHS /usr/include /usr/local/include /opt/homebrew/include)
endif()

# SQLite3
find_package(SQLite3 REQUIRED)
if(NOT SQLite3_FOUND)
    pkg_check_modules(SQLITE3 REQUIRED sqlite3)
    set(SQLite3_LIBRARIES ${SQLITE3_LIBRARIES})
    set(SQLite3_INCLUDE_DIRS ${SQLITE3_INCLUDE_DIRS})
endif()

# ASIO (header-only, используем переменную окружения или стандартные пути)
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
    # ASIO может быть установлен через brew/vcpkg или быть header-only
    # Попробуем найти в стандартных местах
    find_path(ASIO_INCLUDE_DIR asio.hpp
        PATHS
            /opt/homebrew/include
            /usr/local/include
            /usr/include
    )
endif()

# Crow (header-only библиотека)
find_path(CROW_INCLUDE_DIR crow.h
    PATHS
        $ENV{CROW_ROOT}/include
        /usr/include
        /usr/local/include
        /opt/homebrew/include
        /usr/include/crow
        ${CMAKE_SOURCE_DIR}/third_party/crow/include
)

if(CROW_INCLUDE_DIR)
    message(STATUS "Found Crow at: ${CROW_INCLUDE_DIR}")
else()
    message(WARNING "Crow not found in standard locations, trying alternative paths")
    find_path(CROW_INCLUDE_DIR crow/crow.h
        PATHS
            /usr/include
            /usr/local/include
            /opt/homebrew/include
    )
    if(NOT CROW_INCLUDE_DIR)
        message(STATUS "Crow will be searched at compile time (may be in system include paths)")
    endif()
endif()

# Проверяем платформу
if(APPLE)
    message(STATUS "Configuring for macOS")
    
    # Qt - пробуем найти автоматически или через переменную окружения
    if(DEFINED ENV{QT_DIR})
        set(CMAKE_PREFIX_PATH "$ENV{QT_DIR}/lib/cmake" ${CMAKE_PREFIX_PATH})
    elseif(EXISTS "$ENV{HOME}/Qt/6.10.1/macos/lib/cmake")
        set(CMAKE_PREFIX_PATH "$ENV{HOME}/Qt/6.10.1/macos/lib/cmake" ${CMAKE_PREFIX_PATH})
    elseif(EXISTS "/opt/homebrew/opt/qt@6/lib/cmake")
        set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@6/lib/cmake" ${CMAKE_PREFIX_PATH})
    endif()
    
    # Qt Widgets - обязателен для GUI версии
    find_package(QT NAMES Qt6 Qt5 QUIET COMPONENTS Widgets)
    if(NOT QT_FOUND)
        message(FATAL_ERROR "Qt not found! Please install Qt6 or Qt5. You can:\n"
            "  - Install via Homebrew: brew install qt@6\n"
            "  - Set QT_DIR environment variable: export QT_DIR=/path/to/Qt\n"
            "  - Or install Qt from https://www.qt.io/download")
    endif()
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
    message(STATUS "Found Qt ${QT_VERSION_MAJOR}")
    
    # Стандартные пути для macOS
    set(PLATFORM_INCLUDE_DIRS
        /opt/homebrew/include
        /usr/local/include
    )

    # Заголовки GUI (только для macOS)
    set(GUI_HEADERS
        include/windows/start_window.h
        include/windows/main_window.h
        include/windows/mining_window.h
    )
    
    # GUI источники (только для macOS)
    set(GUI_SOURCES
        src/main.cpp
        src/ui/start_window.cpp
        src/ui/main_window.cpp
        src/ui/mining_window.cpp
    )

elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux (Debian/Ubuntu)")
    
    # Стандартные пути для Debian/Ubuntu
    set(PLATFORM_INCLUDE_DIRS
        /usr/include
        /usr/local/include
    )
    
    # Qt не требуется для серверной версии
    set(BUILD_GUI OFF)
endif()

# Общие заголовки
set(COMMON_HEADERS
    include/api/Api.h
    include/api/ApiRegistry.h
    include/blockchain/User.h
    include/blockchain/Transaction.h
    include/blockchain/Miner.h
    include/blockchain/Block.h
    include/blockchain/Blockchain.h
    include/blockchain/Mempool.h
    include/file_sharing/Sending.h
    include/network/Peer.h
    include/network/Message.h
    include/network/CryptoUtils.h
    include/network/Node.h
)

# Общие источники
set(COMMON_SOURCES
    src/api/Api.cpp
    src/blockchain/User.cpp
    src/blockchain/Transaction.cpp
    src/blockchain/Miner.cpp
    src/blockchain/Block.cpp
    src/blockchain/Blockchain.cpp
    src/blockchain/Mempool.cpp
    src/file_sharing/Sending.cpp
    src/network/Peer.cpp
    src/network/CryptoUtils.cpp
    src/network/Node.cpp
)

# Общие include директории
list(APPEND COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${SODIUM_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
    ${PLATFORM_INCLUDE_DIRS}
)

# Добавляем ASIO и Crow если найдены
if(ASIO_INCLUDE_DIR)
    list(APPEND COMMON_INCLUDE_DIRS ${ASIO_INCLUDE_DIR})
endif()

if(CROW_INCLUDE_DIR)
    list(APPEND COMMON_INCLUDE_DIRS ${CROW_INCLUDE_DIR})
endif()

# Собираем для macOS с GUI
if(APPLE)
    set(HEADERS ${GUI_HEADERS} ${COMMON_HEADERS})
    set(SOURCES ${GUI_SOURCES} ${COMMON_SOURCES})
    
    add_executable(Blockchain ${SOURCES} ${HEADERS})
    
    target_include_directories(Blockchain PRIVATE ${COMMON_INCLUDE_DIRS})
    target_compile_definitions(Blockchain PRIVATE ASIO_STANDALONE)
    
    target_link_libraries(Blockchain
        PRIVATE 
        Qt${QT_VERSION_MAJOR}::Widgets
        ${SODIUM_LIBRARIES}
        ${SQLite3_LIBRARIES}
    )
    
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(Blockchain)
    endif()

# Собираем для Linux (серверная версия)
elseif(UNIX AND NOT APPLE)
    set(SOURCES ${COMMON_SOURCES} src/main_server.cpp)
    set(HEADERS ${COMMON_HEADERS})
    
    add_executable(server ${SOURCES} ${HEADERS})
    
    target_include_directories(server PRIVATE ${COMMON_INCLUDE_DIRS})
    target_compile_definitions(server PRIVATE ASIO_STANDALONE)
    
    target_link_libraries(server
        PRIVATE
        ${SODIUM_LIBRARIES}
        ${SQLite3_LIBRARIES}
        pthread
    )

else()
    message(FATAL_ERROR "Unsupported platform")
endif()
