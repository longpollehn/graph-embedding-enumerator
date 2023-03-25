cmake_minimum_required(VERSION 3.24)

project(graph_enumerator)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        OGDF
        GIT_REPOSITORY https://github.com/ogdf/ogdf
)

FetchContent_MakeAvailable(OGDF)

add_executable(graph_enumerator main.cpp)

target_link_libraries(graph_enumerator OGDF COIN)