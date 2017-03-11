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

void start_server(char* ip, uint16_t port) {

	// Start the server. Basically an echo server which receives a byte and send it back

	int server_sock, client_sock, client_len;
	struct sockaddr_in server, client;
	uint64_t count = 10000;

	int sockaddr_len = sizeof(struct sockaddr_in);

	// Create server socket
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("ERROR : Socket creation has failed\n");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);

	// Bind server socket to address
	if ( bind(server_sock, (struct sockaddr*) &server , sizeof(server)) < 0) {
		perror("ERROR: failed to bind");
		exit(1);
	}

	// Listen on the socket
	listen(server_sock , 3);

	// We'll be getting a char value
	char* c;

	// Run server
	while(1) {

		client_sock = accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&sockaddr_len);

		if (client_sock < 0) {
			printf("ERROR: Client accept method failed\n");
			exit(1);
		}

		// Receives the packet and send it back, RTT calculated at client side
		for(uint64_t i =0; i<count; ++i) {
			recv(client_sock, &c, 1, 0);
			send(client_sock, &c, 1, 0);
		}

	}

}

int main(int argc, char** argv) {

	if (argc != 3) {
		printf("ERROR : Usage <executable> <ip> <port>\n");
		exit(1);
	}

	char* server_ip = argv[1];
	uint16_t server_port = atoi(argv[2]);

	printf("Starting server at %s:%d\n", server_ip, server_port);

	start_server(server_ip, server_port);

	return 0;

}
