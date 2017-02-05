/*
 * utils.h
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdint.h>
#include <math.h>

void measure_cpufreq();
uint64_t calc_average(uint64_t* ticks, int iterations, int min, int max, int diff);

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
