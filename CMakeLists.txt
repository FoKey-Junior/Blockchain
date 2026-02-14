cmake_minimum_required(VERSION 3.25)

project(BlockchainApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(PkgConfig REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml QuickControls2 QuickDialogs2)

if(COMMAND qt_standard_project_setup)
    qt_standard_project_setup()
endif()
pkg_check_modules(SODIUM IMPORTED_TARGET libsodium)
if(SODIUM_FOUND)
    set(SODIUM_LINK_LIBS PkgConfig::SODIUM)
else()
    find_library(SODIUM_LIB_FOUND NAMES sodium libsodium PATHS /opt/homebrew/lib /usr/local/lib /usr/lib)
    find_path(SODIUM_INCLUDE_FOUND NAMES sodium.h PATHS /opt/homebrew/include /usr/local/include /usr/include)
    if(SODIUM_LIB_FOUND AND SODIUM_INCLUDE_FOUND)
        set(SODIUM_LINK_LIBS ${SODIUM_LIB_FOUND})
        set(SODIUM_INCLUDE_DIRS ${SODIUM_INCLUDE_FOUND})
    else()
        message(FATAL_ERROR "libsodium not found. Install libsodium-dev (Linux) or brew install libsodium (macOS).")
    endif()
endif()

find_path(ASIO_INCLUDE_DIR asio.hpp
    PATHS
        $ENV{ASIO_ROOT}/include
        /usr/include
        /usr/local/include
        /opt/homebrew/include
)
if(NOT ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "ASIO not found. Install libasio-dev or set ASIO_ROOT.")
endif()

set(APP_HEADERS
    include/core/types.h
    include/core/crypto.h
    include/core/log.h
    include/core/transaction.h
    include/core/block.h
    include/core/blockchain.h
    include/core/mempool.h
    include/core/user.h
    include/network/node.h
    include/storage/database.h
    include/storage/user_store.h
    include/storage/tx_store.h
    include/storage/block_store.h
    include/gui/models.h
    include/gui/app_controller.h
)

set(APP_SOURCES
    src/core/crypto.cpp
    src/core/log.cpp
    src/core/transaction.cpp
    src/core/block.cpp
    src/core/blockchain.cpp
    src/core/mempool.cpp
    src/core/user.cpp
    src/network/node.cpp
    src/storage/database.cpp
    src/storage/user_store.cpp
    src/storage/tx_store.cpp
    src/storage/block_store.cpp
    src/gui/models.cpp
    src/gui/app_controller.cpp
    src/gui/main.cpp
)

qt_add_executable(BlockchainApp
    ${APP_HEADERS}
    ${APP_SOURCES}
)

qt_add_resources(BlockchainApp app_qml_resources
    PREFIX "/qml"
    FILES
        qml/Main.qml
        assets/icon.png
)

target_include_directories(BlockchainApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SODIUM_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
    ${ASIO_INCLUDE_DIR}
)

target_compile_definitions(BlockchainApp PRIVATE ASIO_STANDALONE)

target_link_libraries(BlockchainApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
    Qt6::QuickDialogs2
    ${SODIUM_LINK_LIBS}
    ${SQLite3_LIBRARIES}
)

set_target_properties(BlockchainApp PROPERTIES MACOSX_BUNDLE TRUE)

if(APPLE)
    # Для нормального запуска вне IDE используем стандартный deploy-скрипт Qt.
    qt_generate_deploy_app_script(
        TARGET BlockchainApp
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )

    install(TARGETS BlockchainApp
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin
    )
    install(SCRIPT ${deploy_script})
endif()
