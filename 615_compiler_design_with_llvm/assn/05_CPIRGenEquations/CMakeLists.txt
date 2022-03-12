cmake_minimum_required(VERSION 3.22)
project(Cminus CXX)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# find the libraries
llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

set(ANTLR4CPP_JAR_LOCATION /usr/local/lib/antlr-4.9-complete.jar)
set(GENERATED generated)
set(ANTLR4_FLAGS -Dlanguage=Cpp -visitor -o ${GENERATED})
set(ANTLR4
    java -Xmx500M -cp "${ANTLR4CPP_JAR_LOCATION}" org.antlr.v4.Tool)
set(ANTLR4_LIBS "/usr/lib/x86_64-linux-gnu/libantlr4-runtime.a")
set(ANTLR4_INCLUDES "/usr/include/antlr4-runtime")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I ${ANTLR4_INCLUDES} -I ${GENERATED}")

execute_process(
    COMMAND mkdir -p ${GENERATED}
)
execute_process(
    COMMAND java -Xmx500M -cp "${ANTLR4CPP_JAR_LOCATION}" org.antlr.v4.Tool ${ANTLR4_FLAGS} ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.g4
)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_PROJECT_NAME}.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED}/${CMAKE_PROJECT_NAME}Lexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED}/${CMAKE_PROJECT_NAME}Parser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED}/${CMAKE_PROJECT_NAME}Listener.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/${GENERATED}/${CMAKE_PROJECT_NAME}Visitor.cpp
)

# Link against LLVM libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${ANTLR4_LIBS} ${LLVM_LIBS})
