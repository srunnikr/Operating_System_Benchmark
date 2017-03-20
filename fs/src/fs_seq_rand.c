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

void fs_sequential(const char* filename) {

    uint64_t num_blocks, start, end;
    blksize_t block_size;
    off_t file_size;
    uint32_t loop_count = 1, temp;
    uint64_t readings[loop_count];
    memset(readings, 0, loop_count);

	// flush memory cache before each testing
	system("echo 3 > /proc/sys/vm/drop_caches");
    
	uint32_t fd = open(filename, O_RDONLY);
    if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) < 0) {
        printf("Setting POSIX flag failed\n");
        exit(1);
    }
    file_size = get_file_size(fd);
    block_size = get_block_size(fd);
    num_blocks = file_size/block_size;

	// if file size < 4 KB, then set it to one block
	if (num_blocks == 0) {
		num_blocks = 1;
	}
    
    char* buf = (char*)malloc(4*1024);

    START_RDTSC(start);
    for (uint64_t i=0; i<num_blocks; ++i) {
        temp = read(fd, buf, sizeof(buf));
    }
    END_RDTSCP(end);

    uint64_t total = (end - start);
    double time_ns = (double)total * 0.416;
    double time_us = (double)total / 1000.0;
    // double time_us = time_ns / 1000.0;
    double time_per_block = time_us / (double) num_blocks;
    // double time_ms = time_us / 1000.0;
    // printf("Test file size : %lu\n", file_size);
    // printf("File system block size : %lu\n", block_size);
    // printf("Number of blocks : %"PRIu64"\n", num_blocks);
    printf("Average time for sequential reading %f us for file size %lu\n", time_per_block, file_size);

    free(buf);

}

void fs_random(const char* filename) {

    uint64_t num_blocks, start, end;
    blksize_t block_size;
    off_t file_size;
    uint32_t loop_count = 1, temp;
    uint64_t readings[loop_count];
    memset(readings, 0, loop_count);

	// flush memory cache before each testing
	system("echo 3 > /proc/sys/vm/drop_caches");
    
    uint32_t fd = open(filename, O_RDONLY);
    if (posix_fadvise(fd, 0, 0, POSIX_FADV_DONTNEED) < 0) {
        printf("Setting POSIX flag failed\n");
        exit(1);
    }
    file_size = get_file_size(fd);
    block_size = get_block_size(fd);
    num_blocks = file_size/block_size;

	// if file size < 4 KB, then set it to one block
	if (num_blocks == 0) {
		num_blocks = 1;
	}
    
	char* buf = (char*)malloc(4*1024);

    START_RDTSC(start);
    for (uint64_t i=0; i<num_blocks; ++i) {
        temp = pread(fd, buf, sizeof(buf), ((rand() % num_blocks) * 4096));
    }
    END_RDTSCP(end);

    uint64_t total = (end - start);
    double time_ns = (double)total * 0.416;
    double time_us = (double)total / 1000.0;
    // double time_us = time_ns / 1000.0;
    double time_per_block = time_us / (double) num_blocks;
    // double time_ms = time_us / 1000.0;
    // printf("Test file size : %lu\n", file_size);
    // printf("File system block size : %lu\n", block_size);
    // printf("Number of blocks : %"PRIu64"\n", num_blocks);
    printf("Average time for random reading %f us for file size %lu\n", time_per_block, file_size);

    free(buf);

}

int main(int argc, char const *argv[]) {

	if (argc != 2) {
		printf("ERROR: Usage fs <filename>\n");
		exit(1);
	}

	const char* filename = argv[1];

    fs_sequential(filename);
    fs_random(filename);

	return 0;
}
