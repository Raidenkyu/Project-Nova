include(FetchContent)

FetchContent_Declare(
        cpp-ipc
        GIT_REPOSITORY https://github.com/mutouyun/cpp-ipc/
        GIT_TAG        v1.3.0
)

FetchContent_MakeAvailable(cpp-ipc)