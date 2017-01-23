/*
 * threads.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "threads.h"

/* Function invoked for thread performance measurements
 * Just returns
 */
void* thread_function(void* id) {
	pthread_exit(NULL);
}

void measure_thread(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	pthread_t thread;
	long arg;
	for(int i=0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		__asm__ volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		);

		pthread_create(&thread, NULL, thread_function, (void *)arg);

		__asm__ volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		);

		uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		ticks[i] = (tick2 - tick1);

		// Wait for thread to join before starting next iteration
		pthread_join(thread, NULL);

	}

	uint64_t average = calc_average(ticks, iterations);
	printf("THREAD : Average cycles = %ld\n", average);

}

