cmake_minimum_required(VERSION 2.6)

project(mem)

include_directories(inc)

file(GLOB SOURCES src/*.c)

set( MEM_SRC
    src/mem.c
)

set(GCC_COVERAGE_COMPILE_FLAGS "-ggdb")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_executable(mem ${MEM_SRC})
