/*
 * cpu_measurement.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "cpu_measurements.h"

/* Prototypes for procedure calls
 *
 * Add no-inline GCC attribute to prevent optimizations on the functions
 * This way we get more accurate measurements
 *
 * */

#pragma optimize("", off)

void __attribute__ ((noinline,optimize("-O0"))) func0() {}
void __attribute__ ((noinline)) func1(int arg1) {}
void __attribute__ ((noinline)) func2(int arg1, int arg2) {}
void __attribute__ ((noinline)) func3(int arg1, int arg2, int arg3) {}
void __attribute__ ((noinline)) func4(int arg1, int arg2, int arg3, int arg4) {}
void __attribute__ ((noinline)) func5(int arg1, int arg2, int arg3, int arg4, int arg5) {}
void __attribute__ ((noinline)) func6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {}
void __attribute__ ((noinline)) func7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {}

#pragma optimize("", on)

// End of procedure measurements

void measure_procedure_0arg() {

}

void measure_procedure_1arg() {

}

void measure_procedure_2arg() {

}

void measure_procedure_3arg() {

}

void measure_procedure_4arg() {

}

void measure_procedure_5arg() {

}

void measure_procedure_6arg() {

}

void measure_procedure_7arg() {

}

void measure_syscalls() {

    /*
    As per the x86 coding manual pg 1665, the higher order bits are stored into
    EDX, and EAX stores the lower 32 bit address
    */
    uint32_t high1, low1, high2, low2;
    int i=0;

    uint64_t ticks[1000];
    memset(ticks, 0, 1000*sizeof(uint64_t));

    for(i=0; i<1000; ++i) {

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
    for(int i=0; i<1000; ++i) {
        sum += ticks[i];
    }

    uint64_t avg = sum / 1000;
    printf("Average cycles : %ld\n", avg);

}
