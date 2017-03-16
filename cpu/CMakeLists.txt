cmake_minimum_required(VERSION 2.6)

project(cpu)

include_directories(inc)

file(GLOB SOURCES src/*.c)

set( CPU_SRC
    src/main.c
    src/procedure_call.c
    src/process.c
    src/threads.c
    src/syscall.c
    src/utils.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(cpu ${CPU_SRC})
target_link_libraries(cpu m pthread)
