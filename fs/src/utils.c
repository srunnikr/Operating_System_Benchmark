#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t get_file_size(uint32_t file_desc) {
    // Return the file size of the file pointed by the descriptor
    // https://linux.die.net/man/2/fstat talks about the fstat fields
    struct stat buffer;
    fstat(file_desc, &buffer);
    return buffer.st_size;
}

blksize_t get_block_size(uint32_t file_desc) {
    // https://linux.die.net/man/2/fstat
    // return the block size of the file using fstat
    struct stat buffer;
    fstat(file_desc, &buffer);
    return buffer.st_blksize;
}
