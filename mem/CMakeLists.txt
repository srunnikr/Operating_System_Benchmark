cmake_minimum_required(VERSION 2.6)

project(mem)

include_directories(inc)

file(GLOB SOURCES src/*.c)

set( MEM_SRC
    src/mem.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(mem ${MEM_SRC})
