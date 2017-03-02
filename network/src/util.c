#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

uint64_t calc_reading(uint32_t high, uint32_t low) {

    return ((uint64_t)high << 32) | low;

}

char* get_local_interface_ip(char* ifname) {

	// This function returns the ip address of an interface in the system
	uint32_t sockfd;
	struct ifreq ifr;

	// Create a socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;

	// Get the IP from the interface
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ-1);

	// Clean up and close the socket
	ioctl(sockfd, SIOCGIFADDR, &ifr);
	close(sockfd);

	char* if_address = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

	printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	return if_address;

}
