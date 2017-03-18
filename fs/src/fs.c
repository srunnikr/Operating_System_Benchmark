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

void file_read_time_sequential(const char* filename) {
    uint64_t num_blocks, start, end;
    size_t block_size;
    blksize_t file_size;
    uint32_t loop_count = 1000;
    uint64_t readings[loop_count];
    memset(readings, 0, loop_count);

    for (int i=0; i<loop_count; ++i) {
        uint32_t fd = open(filename, O_RDONLY);
        file_size = get_file_size(fd);
        block_size = get_block_size(fd);
        num_blocks = file_size / block_size;

        // Print stats first time
        if (i == 0) {
            printf("File size : %lu\n", file_size);
            printf("Block size : %lu\n", block_size);
            printf("Number of blocks : %"PRIu64"\n", num_blocks);
        }

        if (fd < 0) {
            printf("ERROR while opening the file\n");
            exit(1);
        }
        // use POSIX_FADV_DONTNEED
        if (posix_fadvise(fd, 0, file_size, POSIX_FADV_DONTNEED) < 0) {
            printf("Setting POSIX flag failed\n");
            exit(1);
        }

        char* data_buff = (char*) malloc (file_size);

        START_RDTSC(start);
        for (uint32_t j = 0; j < num_blocks; j++) {
            read(fd, data_buff, block_size);
        }
        END_RDTSCP(end);

        readings[i] = (end - start);

        close(fd);
        free(data_buff);
    }

    uint64_t total = 0;
    for (uint64_t i = 0; i < loop_count; i++) {
        total += readings[i];
    }
    double avg = (double)total / (double)loop_count;
    double time_ns = avg * 0.416;
    printf("Average time for sequential read of the block %f ns\n", time_ns);

}

int main(int argc, char const *argv[]) {

    if (argc != 2) {
        printf("ERROR: Usage fs <filename>\n");
        exit(1);
    }

    const char* filename = argv[1];

    file_read_time_sequential(filename);

    return 0;
}
