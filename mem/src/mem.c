#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>	
#include <sys/stat.h>
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
		for(uint64_t i=0; i < (middle/64); ++i) {
			uint64_t t0 = arr[0];
			uint64_t t1 = arr[middle+0];
			uint64_t t2 = arr[1];
			uint64_t t3 = arr[middle+1];
			uint64_t t4 = arr[2];
			uint64_t t5 = arr[middle+2];
			uint64_t t6 = arr[3];
			uint64_t t7 = arr[middle+3];
			uint64_t t8 = arr[4];
			uint64_t t9 = arr[middle+4];
			uint64_t t10 = arr[5];
			uint64_t t11 = arr[middle+5];
			uint64_t t12 = arr[6];
			uint64_t t13 = arr[middle+6];
			uint64_t t14 = arr[7];
			uint64_t t15 = arr[middle+7];
			uint64_t t16 = arr[8];
			uint64_t t17 = arr[middle+8];
			uint64_t t18 = arr[9];
			uint64_t t19 = arr[middle+9];
			uint64_t t20 = arr[10];
			uint64_t t21 = arr[middle+10];
			uint64_t t22 = arr[11];
			uint64_t t23 = arr[middle+11];
			uint64_t t24 = arr[12];
			uint64_t t25 = arr[middle+12];
			uint64_t t26 = arr[13];
			uint64_t t27 = arr[middle+13];
			uint64_t t28 = arr[14];
			uint64_t t29 = arr[middle+14];
			uint64_t t30 = arr[15];
			uint64_t t31 = arr[middle+15];
			uint64_t t32 = arr[16];
			uint64_t t33 = arr[middle+16];
			uint64_t t34 = arr[17];
			uint64_t t35 = arr[middle+17];
			uint64_t t36 = arr[18];
			uint64_t t37 = arr[middle+18];
			uint64_t t38 = arr[19];
			uint64_t t39 = arr[middle+19];
			uint64_t t40 = arr[20];
			uint64_t t41 = arr[middle+20];
			uint64_t t42 = arr[21];
			uint64_t t43 = arr[middle+21];
			uint64_t t44 = arr[22];
			uint64_t t45 = arr[middle+22];
			uint64_t t46 = arr[23];
			uint64_t t47 = arr[middle+23];
			uint64_t t48 = arr[24];
			uint64_t t49 = arr[middle+24];
			uint64_t t50 = arr[25];
			uint64_t t51 = arr[middle+25];
			uint64_t t52 = arr[26];
			uint64_t t53 = arr[middle+26];
			uint64_t t54 = arr[27];
			uint64_t t55 = arr[middle+27];
			uint64_t t56 = arr[28];
			uint64_t t57 = arr[middle+28];
			uint64_t t58 = arr[29];
			uint64_t t59 = arr[middle+29];
			uint64_t t60 = arr[30];
			uint64_t t61 = arr[middle+30];
			uint64_t t62 = arr[31];
			uint64_t t63 = arr[middle+31];
			uint64_t t64 = arr[32];
			uint64_t t65 = arr[middle+32];
			uint64_t t66 = arr[33];
			uint64_t t67 = arr[middle+33];
			uint64_t t68 = arr[34];
			uint64_t t69 = arr[middle+34];
			uint64_t t70 = arr[35];
			uint64_t t71 = arr[middle+35];
			uint64_t t72 = arr[36];
			uint64_t t73 = arr[middle+36];
			uint64_t t74 = arr[37];
			uint64_t t75 = arr[middle+37];
			uint64_t t76 = arr[38];
			uint64_t t77 = arr[middle+38];
			uint64_t t78 = arr[39];
			uint64_t t79 = arr[middle+39];
			uint64_t t80 = arr[40];
			uint64_t t81 = arr[middle+40];
			uint64_t t82 = arr[41];
			uint64_t t83 = arr[middle+41];
			uint64_t t84 = arr[42];
			uint64_t t85 = arr[middle+42];
			uint64_t t86 = arr[43];
			uint64_t t87 = arr[middle+43];
			uint64_t t88 = arr[44];
			uint64_t t89 = arr[middle+44];
			uint64_t t90 = arr[45];
			uint64_t t91 = arr[middle+45];
			uint64_t t92 = arr[46];
			uint64_t t93 = arr[middle+46];
			uint64_t t94 = arr[47];
			uint64_t t95 = arr[middle+47];
			uint64_t t96 = arr[48];
			uint64_t t97 = arr[middle+48];
			uint64_t t98 = arr[49];
			uint64_t t99 = arr[middle+49];
			uint64_t t100 = arr[50];
			uint64_t t101 = arr[middle+50];
			uint64_t t102 = arr[51];
			uint64_t t103 = arr[middle+51];
			uint64_t t104 = arr[52];
			uint64_t t105 = arr[middle+52];
			uint64_t t106 = arr[53];
			uint64_t t107 = arr[middle+53];
			uint64_t t108 = arr[54];
			uint64_t t109 = arr[middle+54];
			uint64_t t110 = arr[55];
			uint64_t t111 = arr[middle+55];
			uint64_t t112 = arr[56];
			uint64_t t113 = arr[middle+56];
			uint64_t t114 = arr[57];
			uint64_t t115 = arr[middle+57];
			uint64_t t116 = arr[58];
			uint64_t t117 = arr[middle+58];
			uint64_t t118 = arr[59];
			uint64_t t119 = arr[middle+59];
			uint64_t t120 = arr[60];
			uint64_t t121 = arr[middle+60];
			uint64_t t122 = arr[61];
			uint64_t t123 = arr[middle+61];
			uint64_t t124 = arr[62];
			uint64_t t125 = arr[middle+62];
			uint64_t t126 = arr[63];
			uint64_t t127 = arr[middle+63];
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
		for(uint64_t i=0; i < middle/64; ++i) {
			arr[0] = 0;
			arr[middle+0] = 1;
			arr[1] = 1;
			arr[middle+1] = 2;
			arr[2] = 2;
			arr[middle+2] = 3;
			arr[3] = 3;
			arr[middle+3] = 4;
			arr[4] = 4;
			arr[middle+4] = 5;
			arr[5] = 5;
			arr[middle+5] = 6;
			arr[6] = 6;
			arr[middle+6] = 7;
			arr[7] = 7;
			arr[middle+7] = 8;
			arr[8] = 8;
			arr[middle+8] = 9;
			arr[9] = 9;
			arr[middle+9] = 10;
			arr[10] = 10;
			arr[middle+10] = 11;
			arr[11] = 11;
			arr[middle+11] = 12;
			arr[12] = 12;
			arr[middle+12] = 13;
			arr[13] = 13;
			arr[middle+13] = 14;
			arr[14] = 14;
			arr[middle+14] = 15;
			arr[15] = 15;
			arr[middle+15] = 16;
			arr[16] = 16;
			arr[middle+16] = 17;
			arr[17] = 17;
			arr[middle+17] = 18;
			arr[18] = 18;
			arr[middle+18] = 19;
			arr[19] = 19;
			arr[middle+19] = 20;
			arr[20] = 20;
			arr[middle+20] = 21;
			arr[21] = 21;
			arr[middle+21] = 22;
			arr[22] = 22;
			arr[middle+22] = 23;
			arr[23] = 23;
			arr[middle+23] = 24;
			arr[24] = 24;
			arr[middle+24] = 25;
			arr[25] = 25;
			arr[middle+25] = 26;
			arr[26] = 26;
			arr[middle+26] = 27;
			arr[27] = 27;
			arr[middle+27] = 28;
			arr[28] = 28;
			arr[middle+28] = 29;
			arr[29] = 29;
			arr[middle+29] = 30;
			arr[30] = 30;
			arr[middle+30] = 31;
			arr[31] = 31;
			arr[middle+31] = 32;
			arr[32] = 32;
			arr[middle+32] = 33;
			arr[33] = 33;
			arr[middle+33] = 34;
			arr[34] = 34;
			arr[middle+34] = 35;
			arr[35] = 35;
			arr[middle+35] = 36;
			arr[36] = 36;
			arr[middle+36] = 37;
			arr[37] = 37;
			arr[middle+37] = 38;
			arr[38] = 38;
			arr[middle+38] = 39;
			arr[39] = 39;
			arr[middle+39] = 40;
			arr[40] = 40;
			arr[middle+40] = 41;
			arr[41] = 41;
			arr[middle+41] = 42;
			arr[42] = 42;
			arr[middle+42] = 43;
			arr[43] = 43;
			arr[middle+43] = 44;
			arr[44] = 44;
			arr[middle+44] = 45;
			arr[45] = 45;
			arr[middle+45] = 46;
			arr[46] = 46;
			arr[middle+46] = 47;
			arr[47] = 47;
			arr[middle+47] = 48;
			arr[48] = 48;
			arr[middle+48] = 49;
			arr[49] = 49;
			arr[middle+49] = 50;
			arr[50] = 50;
			arr[middle+50] = 51;
			arr[51] = 51;
			arr[middle+51] = 52;
			arr[52] = 52;
			arr[middle+52] = 53;
			arr[53] = 53;
			arr[middle+53] = 54;
			arr[54] = 54;
			arr[middle+54] = 55;
			arr[55] = 55;
			arr[middle+55] = 56;
			arr[56] = 56;
			arr[middle+56] = 57;
			arr[57] = 57;
			arr[middle+57] = 58;
			arr[58] = 58;
			arr[middle+58] = 59;
			arr[59] = 59;
			arr[middle+59] = 60;
			arr[60] = 60;
			arr[middle+60] = 61;
			arr[61] = 61;
			arr[middle+61] = 62;
			arr[62] = 62;
			arr[middle+62] = 63;
			arr[63] = 63;
			arr[middle+63] = 64;


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
	uint64_t file_size;
	int fd;
	char *fmap; 
	char read;

	// get the file size
	// note that the testing file should be big enough.
	// a resonable size is hundreds of megabytes
	struct stat st;
	stat("test_file", &st);
	file_size = st.st_size;
	printf("Size of the testing file: %"PRIu64" bytes\n", file_size);

	for (uint64_t j = 0; j < loops; j++) {
		
		uint64_t offset = 0;	

		for(uint64_t i = 0; i < page_fault_count; i++) {

			// clear pagecache, dentries and inodes
//			system("sudo purge");	// apply to MacOS
			system("echo 3 > /proc/sys/vm/drop_caches");	// apply to Ubuntu

			if ((fd = open("test_file", O_RDONLY)) < 0) {
				printf("cannot open test_file\n");
				exit(1);
			}

			char *fmap = (char*)mmap(NULL, PAGE_SIZE, PROT_READ, MAP_SHARED, fd, offset);
			
			START_RDTSC(start);
			read = fmap[0];
			END_RDTSCP(end);

			munmap(fmap, PAGE_SIZE);
			close(fd);

			total += (end - start);

			// set offset with some stride to avoid cache on the disk.
			// although we don't know the size of disk cache, we can still set
			// the a reasonable stride to improve measurement accuracy.
			// our tests show that setting a large stride is very important.
			
			// stride is 4 KB * 1024 = 4 MB
			offset += PAGE_SIZE * 1024;	
			
			// avoid overflow of offset
			offset %= file_size;

			// offset should be a multiple of PAGE_SIZE
			// otherwise segmentation fault will be reported when calling mmap
			offset = offset / PAGE_SIZE * PAGE_SIZE;
		}
	}
	
	uint64_t total_pagefaults = loops * page_fault_count;
	double avg_cycles = (double)total / (double)total_pagefaults;

	printf("Average page fault service cycles : %f\n", avg_cycles); 

}


int main() {

	printf("Starting measurement\n");
//	memory_latency(100000);
	memory_bandwidth(100);
	memory_pagefault(1);
	printf("Done!\n");

	return 0;

}
