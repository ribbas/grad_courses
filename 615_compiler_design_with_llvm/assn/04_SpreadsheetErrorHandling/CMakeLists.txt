cmake_minimum_required(VERSION 3.22)
project(spreadsheet-scanner CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(${CMAKE_PROJECT_NAME} SS-Driver.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    FF_List.cpp
    ID_List.cpp 
    Node.cpp 
    Parser.cpp 
    Scanner.cpp 
    SS_Cell.cpp 
    SS-Driver.cpp 
    SS_Scanner_Support.cpp 
)
