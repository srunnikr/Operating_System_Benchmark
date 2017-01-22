#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "procedure_call.h"
#include "syscall.h"

int main(int argc, char** argv) {

	if(argc != 2) {
		printf("Error: Invoke by ./cpu <iterations>\n");
		exit(1);
	}

	int iterations = atoi(argv[1]);

    measure_syscalls(iterations);

    measure_procedure_0arg(iterations);
    measure_procedure_1arg(iterations);
    measure_procedure_2arg(iterations);
    measure_procedure_3arg(iterations);
    measure_procedure_4arg(iterations);
    measure_procedure_5arg(iterations);
    measure_procedure_6arg(iterations);
    measure_procedure_7arg(iterations);

    return 0;

}
