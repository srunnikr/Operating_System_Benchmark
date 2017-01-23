#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "procedure_call.h"
#include "syscall.h"
#include "threads.h"
#include "process.h"
#include "utils.h"

// Make this true if you need to check CPU frequency
#define CPU_FREQ_MEASUREMENT false

int main(int argc, char** argv) {

	if(argc != 2) {
		printf("Error: Invoke by ./cpu <iterations>\n");
		exit(1);
	}

	int iterations = atoi(argv[1]);

	if(CPU_FREQ_MEASUREMENT) {
		measure_cpufreq();
	}

    measure_syscalls(iterations);

    measure_procedure_0arg(iterations);
    measure_procedure_1arg(iterations);
    measure_procedure_2arg(iterations);
    measure_procedure_3arg(iterations);
    measure_procedure_4arg(iterations);
    measure_procedure_5arg(iterations);
    measure_procedure_6arg(iterations);
    measure_procedure_7arg(iterations);

    measure_thread(iterations);

    measure_process(iterations);

    return 0;

}
