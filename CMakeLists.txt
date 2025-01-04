cmake_minimum_required(VERSION 3.27)

project(nova-service)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find Window Management libs like Wayland, Miral and XKBCommon
include(FindPkgConfig)
pkg_check_modules(WAYLAND_CLIENT REQUIRED IMPORTED_TARGET wayland-client)
pkg_check_modules(MIRAL miral REQUIRED)
pkg_check_modules(XKBCOMMON xkbcommon REQUIRED)

# Find Dependencies
find_package(cpp-ipc)
find_package(eventpp)
find_package(seasocks)
find_package(spdlog)
find_package(WebView)

# Add sources directory, supplying both PROJECT_SRC_FILES and PROJECT_INCLUDE_DIR
add_subdirectory("${CMAKE_SOURCE_DIR}/src/")

add_executable(${PROJECT_NAME} ${PROJECT_SRC_FILES})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS}
        ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(
        ${PROJECT_NAME}
        ${MIRAL_LDFLAGS}
        ${XKBCOMMON_LIBRARIES}
        PkgConfig::WAYLAND_CLIENT
        webview::core
        seasocks
        eventpp
        spdlog::spdlog
        ipc
)
