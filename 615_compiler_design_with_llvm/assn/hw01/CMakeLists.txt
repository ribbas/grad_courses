cmake_minimum_required(VERSION 3.16)
project(scanner CXX)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_executable(${CMAKE_PROJECT_NAME} scanner.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    scanner.cpp
)
