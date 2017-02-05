/*
 * cpu_measurement.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#include "procedure_call.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "utils.h"
#include <unistd.h>

/* Prototypes for procedure calls
 *
 * Add no-inline GCC attribute to prevent optimizations on the functions
 * This way we get more accurate measurements
 *
 * */

#pragma optimize("", off)

void __attribute__ ((noinline)) func0() {}
void __attribute__ ((noinline)) func1(int arg1) {}
void __attribute__ ((noinline)) func2(int arg1, int arg2) {}
void __attribute__ ((noinline)) func3(int arg1, int arg2, int arg3) {}
void __attribute__ ((noinline)) func4(int arg1, int arg2, int arg3, int arg4) {}
void __attribute__ ((noinline)) func5(int arg1, int arg2, int arg3, int arg4, int arg5) {}
void __attribute__ ((noinline)) func6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {}
void __attribute__ ((noinline)) func7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {}

//static inline void func0() {}
//static inline void func1(int arg1) {}
//static inline void func2(int arg1, int arg2) {}
//static inline void func3(int arg1, int arg2, int arg3) {}
//static inline void func4(int arg1, int arg2, int arg3, int arg4) {}
//static inline void func5(int arg1, int arg2, int arg3, int arg4, int arg5) {}
//static inline void func6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {}
//static inline void func7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {}

#pragma optimize("", on)

// End of procedure measurements

void measure_procedure_0arg(int iterations) {

    uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure0.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		// start = start_rtdsc();
		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func0();

		__asm__ __volatile__(
				"RDTSCP\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t"
				"CPUID\n\t": "=r" (high2), "=r" (low2)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		// stop = stop_rtdscp();
		start = (((uint64_t)high1 << 32) | low1);
		stop = (((uint64_t)high2 << 32) | low2);

		ticks[i] = stop - start;

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
        sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
    }

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
    printf("FUNC 0 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}

void measure_procedure_1arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure1.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func1(1);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
        sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
    }

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
    printf("FUNC 1 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}

void measure_procedure_2arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure2.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func2(1,2);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
    printf("FUNC 2 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}

void measure_procedure_3arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure3.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func3(1,2,3);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
    printf("FUNC 3 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}

void measure_procedure_4arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure4.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func4(1,2,3,4);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
	printf("FUNC 4 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}

void measure_procedure_5arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure5.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func5(1,2,3,4,5);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
	printf("FUNC 5 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);

}

void measure_procedure_6arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure6.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func6(1,2,3,4,5,6);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
	printf("FUNC 6 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}

void measure_procedure_7arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
    FILE* fp = fopen("logs/procedure7.txt", "w+");

	uint64_t start, stop;

	for(uint64_t i = 0; i<iterations; ++i) {

		__asm__ __volatile__(
				"CPUID\n\t"
				"RDTSC\n\t"
				"mov %%edx, %0\n\t"
				"mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
				:: "%rax", "%rbx", "%rcx", "%rdx"
		);

		func7(1,2,3,4,5,6,7);

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

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

    //double_t avg = (double_t) sum / (double_t) iterations;
	double avg = calc_average(ticks, iterations, -1, -1, 100);
    printf("FUNC 7 ARGS : Average cycles = %f\n\n", avg);

    fprintf(fp, "%f", avg);
    fclose(fp);
	free(ticks);

}
