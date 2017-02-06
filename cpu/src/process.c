/*
 * process.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 *
 *  Last Revision: Feb 5, 2017
 *		Editor: Huan Zhou
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process.h"
#include "utils.h"

void measure_process_creation(int iterations) {
	
	uint32_t high1, low1, high2, low2;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
	FILE* fp = fopen("logs/process_creation.txt","w+");

	for(int i=0; i<iterations; ++i) {

		// Note the start time, call kernel functions to disable preemption & interrupt here
		__asm__ volatile ("CPUID\n\t"
			 "RDTSC\n\t"
			 "mov %%edx, %0\n\t"
			 "mov %%eax, %1\n\t": "=r" (high1), "=r" (low1)
			 :: "%rax", "%rbx", "%rcx", "%rdx"
		 );

		pid_t pid = fork();

		__asm__ volatile ("rdtscp\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t"
			"cpuid\n\t"
			: "=r" (high2), "=r" (low2)
			:: "%rax", "%rbx", "%rcx", "%rdx"
		 );

		if(pid == 0) {
			exit(-1);
		} 

		uint64_t tick1 = ((uint64_t)high1 << 32) | low1;
		uint64_t tick2 = ((uint64_t)high2 << 32) | low2;
		//TODO: Need to calculate overhead and subtract here?
		ticks[i] = (tick2 - tick1);

	}

	for(int i=0; i<iterations; ++i) {
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

	uint64_t average = calc_average(ticks, iterations, 100000, 500000, 100000);
	printf("PROCESS_CREATION : Average cycles = %"PRIu64"\n\n", average);

	fclose(fp);
	free(ticks);
}

void measure_process_switch(int iterations) {
	
	uint64_t start = 0, end = 0;
	uint64_t* ticks = (uint64_t*) malloc (sizeof(uint64_t) * iterations);
	memset(ticks, 0, iterations * sizeof(uint64_t));
	FILE* fp = fopen("logs/process_switch.txt","w+");

	for(int i=0; i<iterations; ++i) {

		int fd[2];
		pipe(fd);
		
		pid_t pid;

		if((pid = fork()) != 0) {
			START_RDTSC(start);
			wait(NULL);
			read(fd[0], (void*)&end, sizeof(uint64_t));
		}else {
			END_RDTSCP(end);
			write(fd[1], (void*)&end, sizeof(uint64_t));
			exit(0);
		}
			
		ticks[i] = (end - start);
	}

	for(int i=0; i<iterations; ++i) {
        fprintf(fp, "%"PRIu64"\n", ticks[i]);
	}

	uint64_t average = calc_average(ticks, iterations, 0, -1, -1 );
	printf("PROCESS_SWITCH : Average cycles = %"PRIu64"\n\n", average);

	fclose(fp);
	free(ticks);
}
