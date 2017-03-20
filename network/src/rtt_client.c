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

void start_client(char* ip, uint16_t port) {

	// Address configuration for client socket
	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	// Measurement counters
	uint32_t high1, low1, high2, low2;
	uint64_t start, end, total;
	uint64_t count = 10000;
	char c = 'a';

	// Create the socket and connect to server
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock < 0) {
		perror("ERROR : Socket creation has failed\n");
		exit(1);
	}

	if (connect(serv_sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
		perror("ERROR: Connection to server failed\n");
		exit(1);
	}

	printf("Connected to server\n");

	total = 0;
	for(uint64_t i=0; i<count; ++i) {

		START_RDTSC(start);
		send(serv_sock, &c, 1, 0);
		recv(serv_sock, &c, 1, 0);
		END_RDTSCP(end);
		total += (end - start);

	}

	printf("Total cycles for %"PRIu64" char RTT : %"PRIu64"\n", count, total);
	double avg_cycles = (double)total / (double)count;
	double time_ns = avg_cycles * (double)0.416;
	double time_ms = time_ns / 1000000;
	printf("Average cycles %f , time in ns %f\n", avg_cycles, time_ns);
	printf("Avg time ms : %f\n", time_ms);

}

int main(int argc, char** argv) {

	if (argc != 3) {
		printf("ERROR : Usage <executable> <server_ip> <server_port>\n");
		exit(1);
	}

	char* server_ip = argv[1];
	uint16_t server_port = atoi(argv[2]);

	printf("Connecting to server at %s:%d\n", server_ip, server_port);

	start_client(server_ip, server_port);

	return 0;

}
