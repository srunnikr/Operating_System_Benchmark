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

void bandwidth_test_local_client() {

	/*
	Code to run bandwidth test locally
	The server and the client runs on local machine. We transfer some huge
	amount of data from client to server and test the overall time it took
	for the transfer
	*/

	char* server_ip = "127.0.0.1"
	char* server_port = 5000

	struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);

	if (connect(serv_sock, (struct sockaddr*) &server, sizeof(server)) < 0) {
        perror("ERROR: Connect failed\n");
        exit(1);
    }

	printf("Connected to server\n");

	uint32_t BUFFSIZE = 1024 * 1024; // 1 MB
	char* msg = (char*) malloc (BUFFSIZE);
	memset(&msg, 0, BUFFSIZE);
	uint64_t start = 0, end = 0;
	uint32_t sent_bytes = 0;

	uint64_t bytes_sent = 0;
	START_RDTSC(start);
	while (bytes_sent != BUFFSIZE) {

		sent_bytes = send(serv_sock, msg + bytes_sent, (BUFFSIZE - bytes_sent));
		if (n < 0) {
			perror("Send failed!\n");
			exit(1);
		}

		bytes_sent += sent_bytes;

	}
	END_RDTSCP(end);

	printf("Cycles taken to transfer data : %"PRIu64"\n", (end- start));

	close(serv_sock);

}

int main(int argc, char const *argv[]) {

	bandwidth_test_local_client();

	return 0;
}
