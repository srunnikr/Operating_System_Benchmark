/*
 * utils.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 *
 *  Last Revision: Feb 4, 2017
 *		Editor: Huan Zhou
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>
#include "utils.h"

void measure_cpufreq() {

	uint32_t high1, low1, high2, low2;
	int iterations = 10;
	int sleep_time = 2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	printf("Measuring CPU frequency: this could take %"PRIu64" s\n", (uint64_t)(iterations * sleep_time));
	printf("Iterations : %d sleepTime : %d\n", iterations, sleep_time);
	for(int i=0; i< iterations; ++i) {
		__asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
			 :: "%rax", "%rbx", "%rcx", "%rdx"
		 );

		sleep(2);

		__asm__ volatile ("rdtscp\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"cpuid\n\t"
			: "=r" (high2), "=r" (low2)
			:: "%rax", "%rbx", "%rcx", "%rdx"
		 );

		uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		ticks[i] = (tick2 - tick1);
		printf("Iteration %d - Cycles = %"PRIu64"\n", i, ticks[i]);

	}

	uint64_t t = 0;
	for (int i=0; i<iterations; ++i) {
		t += ticks[i];
	}
	double a = (double)t / (double)iterations;
	printf("Avg : %f\n", a);
	printf("time per cycle : %f\n", (double)2 / a );

	uint64_t average = (uint64_t)calc_average(ticks, iterations, -1, -1, 100);
	printf("CPU average cycles : %"PRIu64"\n\n", (average / sleep_time));

	fflush(NULL);
	free(ticks);
}

double calc_timeread_overhead(uint64_t iterations) {

	// Function to measure the overhead of RDTSC instruction
    uint32_t high1, low1, high2, low2;
	uint64_t total = 0, start, stop;
    uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
    memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/time_overhead.txt", "w+");

	for (int i=0; i<iterations; ++i) {

        __asm__ __volatile__(
            "CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
            :: "%rax", "%rbx", "%rcx", "%rdx"
        );

        __asm__ __volatile__(
            "RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (high2), "=r" (low2)
            :: "%rax", "%rbx", "%rcx", "%rdx"
        );

        start = (((uint64_t)high1 << 32) | low1);
        stop = (((uint64_t)high2 << 32) | low2);
        ticks[i] = stop - start;
	}

    for(int i=0; i<iterations; ++i) {
        total += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
    }

	//average = (double_t) total / (double_t) iterations;
    double average = calc_average(ticks, iterations, -1, -1, 100);
    printf("Time read overhead : %f\n\n", average);

    fprintf(fp, "%f", average);
	fflush(NULL);
    fclose(fp);
	free(ticks);

	return average;

}

double calc_loop_overhead(uint64_t iterations) {

	// Function to measure overhead of a loop
    uint32_t high1, low1, high2, low2;
	uint64_t total = 0, start, stop;
    FILE* fp = fopen("logs/loop_overhead.txt", "w+");

    __asm__ __volatile__(
        "CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

	for (int i=0; i<iterations; ++i) {
	}

    __asm__ __volatile__(
        "RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (high2), "=r" (low2)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    start = (((uint64_t)high1 << 32) | low1);
    stop = (((uint64_t)high2 << 32) | low2);

	total += (stop - start);
    fprintf(fp, "%"PRIu64"\n", total);

	double average = (double) total / (double) iterations;

    fprintf(fp, "%f", average);
    fclose(fp);

	printf("Loop overhead : %f\n\n", average);
	fflush(NULL);

	return average;

}

/* Parameters:
 * min:	lower bound; values smaller than min will be disgarded,
 *      if there is no need to set lower bound, set it to (-1).
 * max: upper bound; values greater than max will be disgarded,
 *      if there is no need to set upper bound, set it to (-1).
 * diff:difference bound; adjacent difference greater than diff will be disgarded,
 *      if there is no need to set difference, set it to (-1).
 */
double calc_average(uint64_t* ticks,	// ticks array 
					  int iterations,	// times of iterations
					  int min,			// lower bound of cycles
					  int max,			// uppder bound of cycles
					  int diff			// difference bound of two adjacent value
					  ){

	double mean = 0, variance = 0, sd = 0;

	int count = 0;

	uint64_t sum = 0;
	for(int i = 1; i < iterations; ++i) {
		if ((diff >= 0 ? abs(ticks[i] - ticks[i-1]) <= diff : 1) && 
			(min >= 0 ? ticks[i] >= min : 1) &&
			(max >= 0 ? ticks[i] <= max : 1)) {
            count += 1;
			sum += ticks[i];
            continue;
        }
	}

	if (count == 0) {
		printf("iteration = %d but count = 0! Please reset the bounds\n", iterations);
		exit(1);
	}
    
	mean = (double)sum / count;

    for(int i = 1; i < iterations; ++i) {
		if ((diff >= 0 ? abs(ticks[i] - ticks[i-1]) <= diff : 1) && 
			(min >= 0 ? ticks[i] >= min : 1) &&
			(max >= 0 ? ticks[i] <= max : 1)) {
			variance += pow((double)abs((mean - ticks[i])), 2);
		}
    }
	
    variance = variance / count;
    sd = sqrt (variance);

    printf("Count : %d, Variance : %f, Standard Deviation : %f\n", count, variance, sd);
	fflush(NULL);

	return mean;

}
