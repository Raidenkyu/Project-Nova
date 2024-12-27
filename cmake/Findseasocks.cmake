include(FetchContent)

FetchContent_Declare(
        seasocks
        GIT_REPOSITORY https://github.com/mattgodbolt/seasocks.git
        GIT_TAG v1.4.6
)

FetchContent_MakeAvailable(seasocks)