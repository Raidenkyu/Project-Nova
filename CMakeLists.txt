cmake_minimum_required(VERSION 3.27)

project(nova-service)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find Window Management libs like Wayland, Miral and XKBCommon
include(FindPkgConfig)
pkg_check_modules(WAYLAND_CLIENT REQUIRED IMPORTED_TARGET wayland-client)
pkg_check_modules(MIRAL miral REQUIRED)
pkg_check_modules(XKBCOMMON xkbcommon REQUIRED)

# Find WebView
find_package(WebView)
find_package(seasocks)
find_package(eventpp)

# Set Project source files
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB WM_SRC_FILES ${PROJECT_SOURCE_DIR}/src/windowmanager/*.cpp)
file(GLOB UI_SRC_FILES ${PROJECT_SOURCE_DIR}/src/UI/*.cpp)
file(GLOB CORE_SRC_FILES ${PROJECT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB MAIN_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(PROJECT_SRC_FILES ${MAIN_SRC_FILES} ${WM_SRC_FILES} ${UI_SRC_FILES} ${CORE_SRC_FILES})

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
)
