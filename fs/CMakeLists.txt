cmake_minimum_required(VERSION 2.6)

project(fs)

include_directories(inc)

file(GLOB SOURCES src/*.c)

set( FS_SRC
    src/fs_cache.c
)

set( FS_SEQ_RAND
    src/fs_seq_rand.c
    src/utils.c
)

set( FS_CON
	src/fs_contention.c
    src/utils.c
)

set(GCC_COVERAGE_COMPILE_FLAGS "-ggdb")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
add_executable(fs_cache ${FS_SRC})
add_executable(fs_seq_rand ${FS_SEQ_RAND})
add_executable(fs_con ${FS_CON})
