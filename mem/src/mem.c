#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "utils.h"
#include "mem.h"

void memory_test1(uint32_t loop_count) {

	uint32_t loops = loop_count;

	// Create pointers for arrays
	int	**arr;

	// Create a pointer to stride through the array
	void **p;

	// local variables
	uint64_t start, stop;
	uint64_t arr_size, stride_len, i;

	// We measure the array sizes from 2^9 to 2^27 bytes
	uint32_t arr_start_size = 9; // 2^9
	uint32_t arr_end_size = 27; // 2^27


	// Stride length increases in a power of 2
	for (stride_len = 1; stride_len < (2<<10); stride_len *= 2) {

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


int main() {

	printf("Starting measurement\n");
	memory_test1(100000);
	printf("Done!\n");

	return 0;

}
