/*
 * server_rtt.c
 *
 *  Created on: Feb 2, 2017
 *      Author: sreejith unnikrishnan
 */

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

int main(int argc, char const *argv[]) {

    if (argc < 2) {
        printf("ERROR : Usage <executable> <port>\n");
        exit(1);
    }

    int port = atoi(argv[1]);

    // Create socket descriptors and variables
    int server_sock, client_sock, client_len;
    struct sockaddr_in server, client;
    uint32_t high1, low1, high2, low2;
    uint64_t start, end;

    client_len = sizeof(struct sockaddr_in);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("ERROR : Socket creation has failed\n");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind server socket to address
    if ( bind(server_sock, (struct sockaddr*) &server , sizeof(server)) < 0) {
        perror("ERROR: failed to bind");
        exit(1);
    }

    // Listen on the socket
    // Max client connection of 3
    listen(server_sock , 3);

    printf("Server running on port: %d \n", port);

    while(1)
    {
    	client_sock = accept(server_sock, (struct sockaddr*) &client,
                                            (socklen_t*) &client_len);

		if (client_sock < 0) {
            perror("ERROR: failed to accept");
            exit(1);
    	}

        __asm__ volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
        );

        close(client_sock);

        __asm__ volatile ("rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "cpuid\n\t"
            : "=r" (high2), "=r" (low2)
            :: "%rax", "%rbx", "%rcx", "%rdx"
        );

        start = calc_reading(high1, low1);
        end = calc_reading(high2, low2);

		printf("Connection shutdown cycles : %"PRIu64"\n", (end - start));

        // End the loop, for automation script, we cannot interrupt the process
        break;

    }

    close(server_sock);

    return 0;

}
