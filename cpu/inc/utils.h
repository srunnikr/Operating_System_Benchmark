/*
 * utils.h
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 *
 *  Last Revision: Feb 5, 2017
 *		Editor: Huan Zhou
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdint.h>
#include <math.h>

static volatile uint32_t _high, _low;

#define START_RDTSC(start) {	\
    __asm__ __volatile__(		\
        "CPUID\n\t"				\
        "RDTSC\n\t"				\
        "mov %%edx, %0\n\t"		\
        "mov %%eax, %1\n\t": "=r" (_high), "=r" (_low)		\
        :: "%rax", "%rbx", "%rcx", "%rdx"					\
    );		\
	(start) = ((uint64_t)_high << 32) | _low;}

#define END_RDTSCP(end) {		\
    __asm__ __volatile__(		\
        "RDTSCP\n\t"			\
        "mov %%edx, %0\n\t"		\
        "mov %%eax, %1\n\t": "=r" (_high), "=r" (_low)		\
        :: "%rax", "%rbx", "%rcx", "%rdx"					\
    );		\
	(end) = ((uint64_t)_high << 32) | _low;}


void measure_cpufreq();
double calc_average(uint64_t* ticks, int iterations, int min, int max, int diff);

double_t calc_timeread_overhead(uint64_t iterations);
double_t calc_loop_overhead(uint64_t iterations);

static inline uint64_t start_rtdsc(void) {
    uint32_t high, low;
    __asm__ __volatile__(
        "CPUID\n\t"
        "RDTSC\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t": "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    return (((uint64_t)high << 32) | low);
}

static inline uint64_t stop_rtdscp(void) {
    uint32_t  high, low;
    __asm__ __volatile__(
        "RDTSCP\n\t"
        "mov %%edx, %0\n\t"
        "mov %%eax, %1\n\t"
        "CPUID\n\t": "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    return (((uint64_t)high << 32) | low);
}

#endif /* UTILS_H_ */
