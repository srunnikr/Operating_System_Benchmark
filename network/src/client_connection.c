/*
 * client_rtt.c
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

    if (argc < 3) {
        printf("ERROR : Usage <executable> <ip address> <port>\n");
        exit(1);
    }

    // Create an address structure for connecting to server
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    // Create a server socket
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0) {
        perror("ERROR : Socket creation has failed\n");
        exit(1);
    }

    // Establish connection, time the same
    uint32_t high1, low1, high2, low2;
    uint64_t start, end;
    __asm__ volatile ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    if (connect(serv_sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("ERROR: Connect failed\n");
        exit(1);
    }

    __asm__ volatile ("rdtscp\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "cpuid\n\t"
        : "=r" (high2), "=r" (low2)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    // calculate the connection setup time
    start = calc_reading(high1, low1);
    end = calc_reading(high2, low2);

    printf("Connection setup cycles : %"PRIu64"\n", (end-start));
    double time_ns = ((double) (end-start)) * 0.416;
    printf("Connection setup time in ns : %f\n", time_ns);

    start = end = high1 = high2 = low1 = low2 = 0;

    __asm__ volatile ("CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    close(serv_sock);

    __asm__ volatile ("rdtscp\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "cpuid\n\t"
        : "=r" (high2), "=r" (low2)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    start = calc_reading(high1, low1);
    end = calc_reading(high2, low2);

    printf("Connection close cycles : %"PRIu64"\n", (end-start));
    time_ns = (double) (end - start) * 0.416;
    printf("Connection close time in ns: %f\n", time_ns);

    return 0;

 }
