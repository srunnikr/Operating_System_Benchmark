/*
 * utils.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

uint64_t measure_cpufreq() {

	uint32_t high1, low1, high2, low2;
	int iterations = 10;
	int sleep_time = 2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	printf("Measuring CPU frequency: this could take %ld s\n", (uint64_t)(iterations * sleep_time));
	printf("Iterations : %d sleepTime : %d\n", iterations, sleep_time);
	for(int i=0; i< iterations; ++i) {
		__asm__ volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		);
		sleep(2);
		__asm__ volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		);

		uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		ticks[i] = (tick2 - tick1);
		printf("Iteration %d - Cycles = %ld\n", i, ticks[i]);

	}

	uint64_t average = calc_average(ticks, iterations);
	printf("CPU average cycles : %ld\n", (average / sleep_time));

}

uint64_t calc_average(uint64_t* ticks, int iterations) {

	uint64_t average = 0;

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	average = sum / iterations;

	return average;

}
