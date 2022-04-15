cmake_minimum_required(VERSION 3.22)
project(spreadsheet-scanner CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(${CMAKE_PROJECT_NAME} SS_Driver.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    FF_List.cpp
    ID_List.cpp
    Node.cpp
    Parser.cpp
    Parser_Util.cpp
    Scanner.cpp
    SS_Cell.cpp
    SS_TOC.cpp
    SS_Driver.cpp
    SS_Scanner_Support.cpp
)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(
    llvm_libs
    ${LLVM_TARGETS_TO_BUILD}
    support
    core
    irreader
    mc
    mcparser
    native
    option
    orcjit
)

# Link against LLVM libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${llvm_libs})
