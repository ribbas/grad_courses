cmake_minimum_required(VERSION 3.22)
project(Cminus CXX)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# find the libraries
llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

set(CLASSPATH /usr/local/lib/antlr-4.9-complete.jar)
set(GENERATED generated)
set(ANTLR4 java -Xmx500M -cp "${CLASSPATH}" org.antlr.v4.Tool)
set(ANTLR4_FLAGS -Dlanguage=Cpp -visitor -o "${GENERATED}")
set(ANTLR4_LIBS /usr/lib/x86_64-linux-gnu/libantlr4-runtime.a)
set(ANTLR4_INCLUDES /usr/include/antlr4-runtime)
set(ANTLR_GEN_FILE_NAMES
    ${CMAKE_PROJECT_NAME}Lexer
    ${CMAKE_PROJECT_NAME}Parser
    ${CMAKE_PROJECT_NAME}BaseListener
    ${CMAKE_PROJECT_NAME}BaseVisitor
    ${CMAKE_PROJECT_NAME}Listener
    ${CMAKE_PROJECT_NAME}Visitor
)

option(GEN "GEN" OFF)
foreach(GENFILE ${ANTLR_GEN_FILE_NAMES})

    if (NOT(EXISTS "${CMAKE_SOURCE_DIR}/${GENFILE}.h"
        AND EXISTS "${CMAKE_SOURCE_DIR}/${GENFILE}.cpp")
        OR ${GEN})

        execute_process(COMMAND mkdir -p ${GENERATED})
        execute_process(
            COMMAND ${ANTLR4} ${ANTLR4_FLAGS} ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.g4
        )

        foreach(GENFILE ${ANTLR_GEN_FILE_NAMES})
            file(COPY "${CMAKE_BINARY_DIR}/${GENERATED}/${GENFILE}.h"
                DESTINATION ${CMAKE_SOURCE_DIR})
            file(COPY "${CMAKE_BINARY_DIR}/${GENERATED}/${GENFILE}.cpp"
                DESTINATION ${CMAKE_SOURCE_DIR})
        endforeach()

        break()
    endif()
endforeach()
unset(GEN CACHE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I ${ANTLR4_INCLUDES}")

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_PROJECT_NAME}.cpp
    ${CMAKE_PROJECT_NAME}Lexer.cpp
    ${CMAKE_PROJECT_NAME}Parser.cpp
    ${CMAKE_PROJECT_NAME}Listener.cpp
    ${CMAKE_PROJECT_NAME}Visitor.cpp
)
set_source_files_properties(${ANTLR4_GEN_FILES} PROPERTIES GENERATED TRUE)

# Link against LLVM libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${ANTLR4_LIBS} ${LLVM_LIBS})
