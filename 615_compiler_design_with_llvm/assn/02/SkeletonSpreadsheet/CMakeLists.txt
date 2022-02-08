cmake_minimum_required(VERSION 3.22)
project(scanner CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(${CMAKE_PROJECT_NAME} SS-Driver.cpp )
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    Scanner.cpp
    SS_Cell.cpp 
    SS-Driver.cpp 
    SS_Scanner_Support.cpp 
)
