cmake_minimum_required(VERSION 3.15)
project(tp6)

set(CMAKE_CXX_STANDARD 14)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)

include_directories(lib)
include_directories(resources)
add_executable(tp6 main.cpp lib/connection.cpp lib/graphviewer.cpp src/animation_util.cpp src/animation_util.h src/animation_util.cpp src/animation_util.h src/string_util.cpp src/string_util.h)
