#include <stdio.h>
#include <stdlib.h>
#include "client_connection.h"

int main(int argc, char** argv) {

    int server_local_port = 2000;
    char* server_local_ip = "127.0.0.1";

    measure_connection(server_local_ip, server_local_port);

    return 0;

}
