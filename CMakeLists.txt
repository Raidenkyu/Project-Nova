cmake_minimum_required(VERSION 3.9)

project(nova-service)

set(CMAKE_CXX_STANDARD 23)

include(FindPkgConfig)
pkg_check_modules(WAYLAND_CLIENT REQUIRED IMPORTED_TARGET wayland-client)
pkg_check_modules(MIRAL miral REQUIRED)
pkg_check_modules(XKBCOMMON xkbcommon REQUIRED)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB WM_SRC_FILES ${PROJECT_SOURCE_DIR}/src/windowmanager/*.cpp)
file(GLOB MAIN_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(PROJECT_SRC_FILES ${MAIN_SRC_FILES} ${WM_SRC_FILES})

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
)
