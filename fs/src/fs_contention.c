#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

#define BLOCKSIZE	4096

double fs_random_read(const char* filename) {

    uint64_t start, end, total;
    uint64_t num_blocks, read_blocks;
    blksize_t block_size;
    off_t file_size;
    uint32_t loop_count = 100, temp;
	char* buf = (char*)malloc(BLOCKSIZE);

	total = 0;
	for (uint64_t i = 0; i < loop_count; i++) {
		
		// flush memory cache before each testing
		system("echo 3 > /proc/sys/vm/drop_caches");
		
		uint32_t fd = open(filename, O_RDONLY);
		if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) < 0) {
			printf("Setting POSIX flag failed\n");
			exit(1);
		}
		file_size = get_file_size(fd);
		block_size = get_block_size(fd);
		
		if (block_size < BLOCKSIZE) {
			printf("block_size = 0, please check whether the file exists\n");
			exit(1);
		}
		
		num_blocks = file_size/block_size;
		read_blocks = num_blocks / 10;
		// only read num_blocks/10 times in each loop, in order to avoid 
		// buffer cache in memory

		// each loop only read 
		START_RDTSC(start);
		for (uint64_t i = 0; i < read_blocks; ++i) {
			temp = pread(fd, buf, BLOCKSIZE, ((rand() % num_blocks) * 4096));
		}
		END_RDTSCP(end);

		close(fd);
		total += (end - start);
	}
    
	double time_ns = (double)total * 0.416;
    double time_us = time_ns / 1000.0;
    double time_us_per_block = time_us / (double) (read_blocks * loop_count);
	off_t file_size_MB = file_size / (1024 * 1024);
    // double time_ms = time_us / 1000.0;
    // printf("Test file size : %lu\n", file_size);
    // printf("File system block size : %lu\n", block_size);
    // printf("Number of blocks : %"PRIu64"\n", num_blocks);
    
	// printf("Random reading per block (us): %f us, file size (MB): %lu\n", time_us_per_block, file_size_MB);

    free(buf);
	return time_us_per_block;

}

int main(int argc, char const *argv[]) {

	if (argc != 3) {
		printf("ERROR: Usage fs <filename>\n");
		exit(1);
	}

	const char* filename = argv[1];
	const char* isPrint = argv[2];

//	printf("filename is : %s\n", filename);

	if(strcmp(isPrint, "1") == 0) {
		double time;
		time = fs_random_read(filename);
		printf("read 64MB file per block time (us): %f\n", time);
	}

	return 0;
}
