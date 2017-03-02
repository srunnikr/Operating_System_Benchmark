#include <stdio.h>
#include <stdlib.h>
#include "client_connection.h"
#include "util.h"

int main(int argc, char** argv) {

    int server_local_port = 2000;
    char* server_local_ip = "127.0.0.1";

    //measure_connection(server_local_ip, server_local_port);
    char* result = get_local_interface_ip("wlp3s0");

    printf("returned %s\n", result);

    return 0;

}
