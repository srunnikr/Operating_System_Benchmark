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

set( CLIENT_SRC_BW
    src/bandwidth_client.c
    src/util.c
)

set( SERVER_SRC_BW
    src/bandwidth_server.c
    src/util.c
)

set( MAIN_SRC
	src/main.c
	src/util.c
)

set( SERVER_RTT
	src/rtt_server.c
	src/util.c
)

set( CLIENT_RTT
	src/rtt_client.c
	src/util.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(client_conn ${CLIENT_SRC})
add_executable(server_conn ${SERVER_SRC})

add_executable(client_bw ${CLIENT_SRC_BW})
add_executable(server_bw ${SERVER_SRC_BW})

add_executable(server_rtt ${SERVER_RTT})
add_executable(client_rtt ${CLIENT_RTT})

add_executable(main ${MAIN_SRC})
