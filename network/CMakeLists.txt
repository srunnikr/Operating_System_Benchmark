cmake_minimum_required(VERSION 2.6)

project(network)

include_directories(inc)

file(GLOB SOURCES src/*.c)

set( CLIENT_SRC
    src/client_connection.c
    src/util.c
)

set ( SERVER_SRC
    src/server_connection.c
    src/util.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(client_conn ${CLIENT_SRC})
add_executable(server_conn ${SERVER_SRC})
