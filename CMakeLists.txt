cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        OGDF
        GIT_REPOSITORY https://github.com/ogdf/ogdf
)
FetchContent_MakeAvailable(OGDF)

add_executable(compute_crossing main.cpp)
target_link_libraries(compute_crossing OGDF COIN)