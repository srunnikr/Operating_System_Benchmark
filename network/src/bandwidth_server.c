#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "util.h"

void bandwidth_test_local_server() {

	// Create socket descriptors and variables
    int server_sock, client_sock, client_len;
    struct sockaddr_in server, client;
    uint32_t high1, low1, high2, low2;
    uint64_t start, end;

}
