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

double file_read_cache(const char* filename, uint64_t read_size) {

	uint64_t start, end, total_cycles;

	// flush cache for each testing
	system("echo 3 > /proc/sys/vm/drop_caches");
	
	// first read, load the file to memory 
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("ERROR while opening the file\n");
		exit(1);
	}

	// set POSIX_FADV_WILLNEED, will read in the future
	if (posix_fadvise(fd, 0, read_size, POSIX_FADV_WILLNEED) < 0) {
		printf("Setting POSIX flag failed\n");
		exit(1);
	}
	
	char* data_buff = (char*)malloc(BLOCKSIZE);
	ssize_t read_bytes = 0;
	uint64_t read_count = read_size / BLOCKSIZE;
	
	for (uint64_t i = 0; i < read_count; i++) {
		read_bytes = read(fd, data_buff, BLOCKSIZE);
		if (read_bytes <= 0) {
			printf("read return wrong\n");
			exit(1);
		}
	}

	close(fd);

	// second read, should use file system cache
	total_cycles = 0;
		
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("ERROR while opening the file\n");
		exit(1);
	}

	// set POSIX_FADV_WILLNEED
	if (posix_fadvise(fd, 0, read_size, POSIX_FADV_WILLNEED) < 0) {
		printf("Setting POSIX flag failed\n");
		exit(1);
	}

	for (uint64_t j = 0; j < read_count; j++) {

		START_RDTSC(start);
		read_bytes = read(fd, data_buff, BLOCKSIZE);
		END_RDTSCP(end);
		
		if (read_bytes <= 0) {
			printf("read return wrong\n");
			exit(1);
		}
		
		total_cycles += (end - start);
	}

	close(fd);
	free(data_buff);

	double time_ns = total_cycles * 0.416;
	return time_ns;
}

int main(int argc, char const *argv[]) {

	if (argc != 2) {
		printf("ERROR: Usage fs <filename>\n");
		exit(1);
	}

	const char* filename = argv[1];
	printf("filename is: %s\n", filename);

	uint64_t array_size = 13;
	uint64_t read_size[array_size];

	// set read size to gigabytes
	// test from 1 GB to 13 GB
	for (uint64_t i = 0; i < array_size; i++) {
		read_size[i] = (i + 1) * 1024 * 1024 * 1024;
	}

	double time_ns, time_per_block;
	uint64_t total_blocks, read_size_MB;

	for (uint64_t i = 0; i < array_size; i++) {
		time_ns = file_read_cache(filename, read_size[i]);
		total_blocks = read_size[i] / BLOCKSIZE;
		time_per_block = time_ns / total_blocks;
		read_size_MB = read_size[i] / (1024 * 1024);

		printf("read size (MB): %"PRIu64", average time per block (ns): %f\n",
				read_size_MB, time_per_block);
	}

	return 0;
}
