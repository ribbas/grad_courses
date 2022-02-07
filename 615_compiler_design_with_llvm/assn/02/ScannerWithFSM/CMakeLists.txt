cmake_minimum_required(VERSION 3.22)
project(scanner CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(${CMAKE_PROJECT_NAME} HW1-Driver.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    getID.cpp 
    getKeyword.cpp 
    getNumber.cpp 
    getSymbol.cpp 
    getToken.cpp 
    getWhiteSpace.cpp
    HW1-Driver.cpp
    inputError.cpp 
    Token.cpp 
)
