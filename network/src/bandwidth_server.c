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

	if (argc < 2) {
		printf("ERROR : Usage <executable> <ip> <port>\n");
		exit(1);
	}

	printf("Starting server\n");

	int port = atoi(argv[2]);
	char* ip = argv[1];

	// Create socket descriptors and variables
	int server_sock, client_sock, client_len;
	struct sockaddr_in server, client;
	uint32_t high1, low1, high2, low2;
	uint64_t start, end, total =0;

	client_len = sizeof(struct sockaddr_in);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("ERROR : Socket creation has failed\n");
		exit(1);
	}

	server.sin_family = AF_INET;
	//server.sin_addr.s_addr = INADDR_ANY;
	server.sin_addr.s_addr = inet_addr(ip);
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

	while(1) {

		// Wait for client connection and handle it
		client_sock = accept(server_sock, (struct sockaddr*) &client,
		                                            (socklen_t*) &client_len);

		if (client_sock < 0) {
			perror("ERROR: failed to accept");
			exit(1);
		}

		uint32_t BUFFSIZE = 1024 * 1024; // 1 MB

		for (int i=0; i<1024; ++i) {

			// Allocate buffer to hold data from client
			char* msg = (char*) malloc (BUFFSIZE * sizeof(char));
			if (!msg) {
				printf("ERROR: Malloc failed\n");
				exit(1);
			}

			memset(msg, '0', BUFFSIZE);
			uint32_t totalSent = 0;
			int32_t sent = 0;


			START_RDTSC(start);

			// Send data till BUFFSIZE
			while(totalSent < BUFFSIZE) {

				sent = send(client_sock, msg + totalSent, BUFFSIZE - totalSent, 0);
				if (sent < 0) {
					printf("ERROR: sending to socket\n");
					exit(1);
				}
				totalSent += sent;

			}

			END_RDTSCP(end);

			total += (end-start);

			free(msg);

		}

		printf("Time at server side to get all data : %"PRIu64"\n", total);
		double time_ns = (double)total * 0.416;
		double time_ms = time_ns / 1000000;
		double total_bytes = (double)BUFFSIZE * 1024;
		double total_MB = total_bytes / (1024 * 1024);
		double bw = (total_MB) / time_ms;
		printf("The time taken: %f ms\n", time_ms);
		printf("Total BW : %f MB/s\n", bw);

		close(client_sock);

	}

	return 0;

}
