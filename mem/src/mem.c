#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "utils.h"
#include "mem.h"

void memory_test1(int loops) {

	uint32_t pow_limit = 27;
	uint64_t start, stop;

	uint64_t size = 6; // start from 2^6 = 64
	char a;

	for(; size < pow_limit; ++size) {

		// Main loop where we will vary the array size
		uint64_t arrSize = 1 << size;
		char* arr = (char *) malloc (arrSize * sizeof(char));
		memset(arr, 0, arrSize);

		// Start the measurement
		START_RDTSC(start);
		// Run loop for loops times
		for (uint32_t i = 0; i < loops; ++i) {
			a = arr[i];
		}
		END_RDTSCP(stop);

		printf("Cycles taken : %f\n", (double)((stop - start)/(double)loops));

	}

}


int main(int argc, char** argv) {

	printf("Starting memory tests\n");

	memory_test1(100000);

}
