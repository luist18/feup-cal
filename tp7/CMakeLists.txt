cmake_minimum_required(VERSION 3.10)
project(tp7)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(tp7 main.cpp test/tests.cpp src/graph.h src/mutable_priority_queue.h)

target_link_libraries(tp7 gtest gtest_main)
