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


int main(int argc, char** argv) {

	uint8_t port = 5000;

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

	// Allocate buffer to hold data from client
	uint32_t BUFFSIZE = 1024 * 1024; // 1 MB
	char* msg = (char*) malloc (BUFFSIZE);
	memset(&msg, 0, BUFFSIZE);
	uint32_t totalRcvd = 0;
	int32_t rcvd = 0;

	printf("Server running on port: %d \n", port);

	while(1) {

		// Wait for client connection and handle it
		client_sock = accept(server_sock, (struct sockaddr*) &client,
		                                            (socklen_t*) &client_len);

		if (client_sock < 0) {
			perror("ERROR: failed to accept");
			exit(1);
		}

		START_RDTSC(start);

		while(totalRcvd < BUFFSIZE) {

			rcvd = read(client_sock, msg + totalRcvd, BUFFSIZE - totalRcvd);
			if (rcvd < 0) {
				printf("ERROR: reading from socket\n");
				exit(1);
			}
			totalRcvd += rcvd;

		}

		END_RDTSCP(end);

		printf("Time at server side to get all data : %d", (end - start));

		close(client_sock);

		break;

	}

	return 0;

}
