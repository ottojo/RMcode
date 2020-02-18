cmake_minimum_required(VERSION 3.15)
project(RMCode)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -Weffc++  -mtune=native -march=native")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("DEBUG BUILD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -ggdb -fsanitize=address --coverage")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

include_directories(lib)
add_executable(RMCode main.cpp)

find_package(benchmark)
if (benchmark_FOUND)
    add_executable(benchmark benchmark.cpp)
    target_link_libraries(benchmark benchmark::benchmark)
endif (benchmark_FOUND)