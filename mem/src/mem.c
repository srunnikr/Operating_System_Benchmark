#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>	
#include "utils.h"
#include "mem.h"

void memory_latency(uint32_t loop_count) {

	printf("Starting memory latency test...\n");
	
	uint32_t loops = loop_count;

	// Create pointers for arrays
	int	**arr;

	// Create a pointer to stride through the array
	void **p;

	// local variables
	uint64_t start, stop;
	uint64_t arr_size, stride_len, i;

	// We measure the array sizes from 2^9 to 2^28 bytes
	uint32_t arr_start_size = 9; // 2^9
	uint32_t arr_end_size = 28; // 2^28


	// Stride length increases in a power of 2
	for (stride_len = 1; stride_len < (2<<16); stride_len *= 2) {

		// For each stride, allocate arrays of different sizes
		for (arr_size = arr_start_size; arr_size <= arr_end_size; arr_size++) {

			arr = malloc(1 << arr_size);
			if (! arr) {

				printf("Failed to allocate memory for array\n");
				exit(1);

			}

			// Set pointers to access the next stride location
			for (i = 0; i + 1 < (1 << arr_size) / (stride_len * sizeof(*arr)); i++) {

				arr[i * stride_len] = (int *)(arr + ((i + 1) * stride_len));

			}

			// Ensure the last pointer points to start
			arr[i * stride_len] = (int *)arr;

			// Set p to beginning
			p = (void **)arr;


			// Run the tests
			START_RDTSC(start);
			for (i = 0; i < loops; ++i) {
				p = *p;
			}
			END_RDTSCP(stop);

			// Calculate the average cycles for this particular array size for the given stride length
			double res =  (double)(stop - start) / (double)loops;

			printf("stride %"PRIu64" and size %"PRIu64" = %f\n", stride_len, arr_size, res);

			// We have huge chunks of memory, free to avoid segmentation faults
			free(arr);

		}

	}

}


void memory_bandwidth(uint64_t loops) {

	/*
	 * This test will measure the memory bandwidth of the system
	 * */
	printf("Starting memory bandwidth test...\n");

	uint64_t start, end;

	uint64_t arr_size = 64 * 1024 * 1024; // 64 * 8 MB
	uint64_t* p = NULL;

	// Allocate the array
	uint64_t* arr = (uint64_t*) malloc (arr_size * sizeof(uint64_t));
	if (!arr) {
		printf("Error while allocating the array\n");
		exit(1);
	}
	memset(arr, 0, arr_size * sizeof(uint64_t));

	double read_bandwidth, write_bandwidth;
	uint64_t middle = arr_size / 2;
	uint64_t total = 0;

	// Read bandwidth
	for (uint64_t j = 0; j < loops; ++j) {
		START_RDTSC(start);
		for(uint64_t i=0; i < middle; ++i) {
			uint64_t t1 = arr[i];
			uint64_t t2 = arr[middle+i];
		}
		END_RDTSCP(end);
		total += (end - start);
	}

	// from cpu experiment 1 cycle = 0.416 ns

	uint64_t total_read_size = loops * arr_size;
	double total_read_size_MB = (double) (8 * total_read_size) / (1024 * 1024);
	double total_time = (double) total * 0.416 * 1e-9;
	read_bandwidth = total_read_size_MB / total_time;

	printf("Total read size : %"PRIu64" and total time in s :%f\n", total_read_size, total_time);
	printf("Read bandwidth : %f\n", read_bandwidth);


	// write bandwidth
	total = 0;
	for (uint64_t j = 0; j < loops; ++j) {
		START_RDTSC(start);
		for(uint64_t i=0; i < middle; ++i) {
			arr[i] = 1;
			arr[middle+i] = 2;
		}
		END_RDTSCP(end);
		total += (end - start);
	}

	uint64_t total_write_size = loops * arr_size;
	double total_write_size_MB = (double) (8 * total_write_size) / (1024 * 1024);
	total_time = (double)total * 0.416 * 1e-9;
	write_bandwidth = total_write_size_MB / total_time;

	printf("Total write size : %"PRIu64" and total time in s :%f\n", total_write_size, total_time);
	printf("Write bandwidth : %f\n", write_bandwidth);


	// free memory
	free(arr);
}

void memory_pagefault(uint64_t loops) {

	printf("Starting memory page fault test...\n");
	
	uint64_t PAGE_SIZE = 4096;			// confirm this in your machine
	uint64_t page_fault_count = 100;	// set page fault times in each loop

	uint64_t start, end, total = 0;
	int fd;
	char *fmap; 
	char read;

	for (uint64_t j = 0; j < loops; j++) {
		
		uint64_t offset = 0;	

		for(uint64_t i = 0; i < page_fault_count; i++) {
			
			if ((fd = open("test_file", O_RDONLY)) < 0) {
				printf("can’t open test_file\n");
				exit(1);
			}
			char *fmap = (char*)mmap(NULL, PAGE_SIZE, PROT_READ, MAP_SHARED, fd, offset);
			
			START_RDTSC(start);
			read = fmap[0];
			END_RDTSCP(end);

			munmap(fmap, PAGE_SIZE);
			close(fd);

			total += (end - start);
			offset += PAGE_SIZE;	
		}
	}
	
	uint64_t total_pagefaults = loops * page_fault_count;
	double avg_cycles = (double)total / (double)total_pagefaults;

	printf("Average page fault service cycles : %f\n", avg_cycles); 

}


int main() {

	printf("Starting measurement\n");
	memory_latency(100000);
	memory_bandwidth(100);
	memory_pagefault(1);
	printf("Done!\n");

	return 0;

}
