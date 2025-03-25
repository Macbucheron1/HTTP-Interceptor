cmake_minimum_required(VERSION 3.10)
project(HTTP-Interceptor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(interceptor src/main.cpp)
