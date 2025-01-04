# Set Project include directory
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

file(GLOB CORE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp)
file(GLOB LOG_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/logger/*.cpp)
file(GLOB SERVICE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/service/*.cpp)
file(GLOB UI_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/UI/*.cpp)
file(GLOB WM_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/windowmanager/*.cpp)

# Set project source files list
set(PROJECT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CORE_SRC_FILES}
        ${LOG_SRC_FILES}
        ${SERVICE_SRC_FILES}
        ${UI_SRC_FILES}
        ${WM_SRC_FILES}
        PARENT_SCOPE
)


# Add demo subdirectory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")