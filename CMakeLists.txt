cmake_minimum_required(VERSION 3.9)

project(nova-service)

set(CMAKE_CXX_STANDARD 23)

include(FindPkgConfig)
pkg_check_modules(MIRAL miral REQUIRED)
pkg_check_modules(XKBCOMMON xkbcommon REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${MIRAL_LDFLAGS}
  ${XKBCOMMON_LIBRARIES}
)
