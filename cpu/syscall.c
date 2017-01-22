/*
 * syscall.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "syscall.h"

void measure_syscalls(int iterations) {

    /*
    As per the x86 coding manual pg 1665, the higher order bits are stored into
    EDX, and EAX stores the lower 32 bit address
    */
    uint32_t high1, low1, high2, low2;
    int i=0;

    uint64_t ticks[iterations];
    memset(ticks, 0, iterations*sizeof(uint64_t));

    for(i=0; i<iterations; ++i) {

        // Call kernel module function that disables interrupts
        __asm__ volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
        );

        getpid();

        __asm__ volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
        );
        // Call kernel module funtion that enables interrupts

        uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
        uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
        ticks[i] = (tick2 - tick1);

    }

    uint64_t sum = 0;
    for(int i=0; i<iterations; ++i) {
        sum += ticks[i];
    }

    uint64_t avg = sum / iterations;
    printf("SYSCALLS : Average cycles = %ld\n", avg);

}
