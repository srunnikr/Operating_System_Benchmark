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

    calc_timeread_overhead(iterations);
    calc_loop_overhead(iterations);

    measure_syscalls(iterations);
    measure_syscalls_ppid(iterations);

    measure_procedure_0arg(iterations);
    measure_procedure_1arg(iterations);
    measure_procedure_2arg(iterations);
    measure_procedure_3arg(iterations);
    measure_procedure_4arg(iterations);
    measure_procedure_5arg(iterations);
    measure_procedure_6arg(iterations);
    measure_procedure_7arg(iterations);

    measure_process_creation(iterations);
    measure_process_switch(iterations);

    measure_thread_creation(iterations);
    measure_thread_switch(iterations);

    return 0;

}
