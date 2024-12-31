include(FetchContent)

FetchContent_Declare(
        eventpp
        GIT_REPOSITORY https://github.com/wqking/eventpp
        GIT_TAG        v0.1.3
)

FetchContent_MakeAvailable(eventpp)