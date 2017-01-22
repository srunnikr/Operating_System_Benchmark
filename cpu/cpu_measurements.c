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

void measure_procedure_0arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func0();

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 0 ARGS : Average cycles = %ld\n", avg);
}

void measure_procedure_1arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func1(1);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 1 ARGS : Average cycles = %ld\n", avg);

}

void measure_procedure_2arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func2(1,2);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 2 ARGS : Average cycles = %ld\n", avg);

}

void measure_procedure_3arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func3(1,2,3);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 3 ARGS : Average cycles = %ld\n", avg);

}

void measure_procedure_4arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func4(1,2,3,4);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 4 ARGS : Average cycles = %ld\n", avg);

}

void measure_procedure_5arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func5(1,2,3,4,5);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 5 ARGS : Average cycles = %ld\n", avg);

}

void measure_procedure_6arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func6(1,2,3,4,5,6);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 6 ARGS : Average cycles = %ld\n", avg);

}

void measure_procedure_7arg(int iterations) {

	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));

	for(uint64_t i = 0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
		 );

		 func7(1,2,3,4,5,6,7);

		 __asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high2), "=r" (low2)
		 );

		 uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		 uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		 ticks[i] = (tick2 - tick1);

	}

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	uint64_t avg = sum / iterations;
	printf("FUNC 7 ARGS : Average cycles = %ld\n", avg);

}

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
