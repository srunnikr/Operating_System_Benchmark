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

	uint64_t average = calc_average(ticks, iterations);
	printf("CPU average cycles : %"PRIu64"\n\n", (average / sleep_time));

}

double_t calc_timeread_overhead(uint64_t iterations) {

	// Function to measure the overhead of RDTSC instruction
    uint32_t high1, low1, high2, low2;
	uint64_t total = 0, start, stop;
	double_t average;
    uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
    memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/time_overhead.txt", "w+");

	for (uint64_t i = 0; i<iterations; ++i) {

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
    average = calc_average(ticks, iterations);
    printf("Time read overhead : %f\n\n", average);

    fprintf(fp, "%f", average);
    fclose(fp);

	return average;

}

double calc_loop_overhead(uint64_t iterations) {

	// Function to measure overhead of a loop
    uint32_t high1, low1, high2, low2;
	uint64_t total = 0, start, stop;
    FILE* fp = fopen("logs/loop_overhead.txt", "w+");
	double average;

    __asm__ __volatile__(
        "CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

	for (uint64_t i = 0; i<iterations; ++i) {
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

	average = (double_t) total / (double_t) iterations;

    fprintf(fp, "%f", average);
    fclose(fp);

	printf("Loop overhead : %f\n\n", average);

	return average;

}

uint64_t calc_average(uint64_t* ticks, int iterations) {

	uint64_t mean = 0;
    double variance = 0, sd = 0;

    int iter = iterations;

	uint64_t sum = 0;
	for(int i=0; i<iter; ++i) {
        if (i > 0 && (ticks[i] - ticks[i-1]) > 100) {
            iterations -= 1;
            continue;
        }
		sum += ticks[i];
	}

    mean = sum / iterations;

    for(int i=0; i<iter; ++i) {
        if (i > 0 && (ticks[i] - ticks[i-1]) > 100) {
            continue;
        }
        variance += pow((double)abs((mean - ticks[i])), 2);
    }

    variance = variance / iterations;
    sd = sqrt (variance);

    printf("Variance : %f, Standard Deviation : %f\n", variance, sd);

	return mean;

}
