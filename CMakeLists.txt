cmake_minimum_required(VERSION 3.17)
project(TPP2D)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
include(include/CMakeLists.txt)
include(src/CMakeLists.txt)

add_executable(TPP2D ${sources})