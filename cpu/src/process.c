/*
 * process.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process.h"
#include "utils.h"

void measure_process(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(int i=0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		__asm__ volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		);

		pid_t id = fork();

		if(id < 0) {
			printf("ERROR: fork failed\n");
			exit(-1);
		}

		if(id == 0) {
			exit(-1);
		} else {
			wait(NULL);
			__asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
			);

			uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
			uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
			//TODO: Need to calculate overhead and subtract here?
			ticks[i] = (tick2 - tick1);
		}

	}

	uint64_t average = calc_average(ticks, iterations);
	printf("PROCESS : Average cycles = %ld\n", average);

}
