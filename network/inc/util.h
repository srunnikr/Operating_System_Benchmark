#ifndef UTIL_H
#define UTIL_H

uint64_t calc_reading(uint32_t high, uint32_t low);

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

#endif
