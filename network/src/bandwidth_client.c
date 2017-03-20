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

void bandwidth_test_local_client(const char* server_ip, uint16_t server_port) {

	/*
	Code to run bandwidth test locally
	The server and the client runs on local machine. We transfer some huge
	amount of data from client to server and test the overall time it took
	for the transfer
	*/

//	char* server_ip = "127.0.0.1";
//	uint16_t server_port = 5000;

	struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);

	// Create socket
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock < 0) {
		perror("ERROR : Socket creation has failed\n");
		exit(1);
	}

	// Connect to server
	if (connect(serv_sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("ERROR: Connect failed\n");
        exit(1);
    }

	printf("Connected to server\n");

	uint32_t BUFFSIZE = 1024 * 1024; // 1 MB
	uint64_t total = 0;
	uint64_t min = INTMAX_MAX;

	// Do the experiment
	for(int i=0; i<1024; ++i) {

		char* msg = (char*) malloc (BUFFSIZE);
		memset(msg, '0', BUFFSIZE);
		uint64_t start = 0, end = 0;
		uint32_t recv_bytes = 0;

		START_RDTSC(start);

		recv_bytes = recv(serv_sock, msg, BUFFSIZE, MSG_WAITALL);

		END_RDTSCP(end);

		if (recv_bytes < 0) {
			perror("Receive failed!\n");
			exit(1);
		}

		total += (end-start);

		if ((end - start) < min) {
			min = (end - start);
		}

		//printf("Min: %"PRIu64"\n", min);

		free(msg);

	}

	printf("Cycles taken to transfer data : %"PRIu64"\n", total);
	double time_ns = (double)min * 0.416;
	double time_ms = time_ns / 1000000;
	printf("The time taken: %f ms\n", time_ms);
	double total_bytes = (double)BUFFSIZE * 1024;
	double total_MB = total_bytes / (1024 * 1024);
	double bw = (total_MB) / time_ms;
	printf("The time taken: %f ms\n", time_ms);
	printf("Total BW : %f MB/s\n", bw);

	close(serv_sock);

}

int main(int argc, char const *argv[]) {

	if (argc != 3) {
		printf("ERROR : Usage <executable> <ip address> <port>\n");
		exit(1);
	}

	const char* server_ip = argv[1];
	uint16_t server_port = atoi(argv[2]);

	bandwidth_test_local_client(server_ip, server_port);

	return 0;
}
