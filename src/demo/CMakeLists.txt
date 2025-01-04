project(demo-service)

add_executable(${PROJECT_NAME} demo.cpp)

target_link_libraries(${PROJECT_NAME} ipc)
