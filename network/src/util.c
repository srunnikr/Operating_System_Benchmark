#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"

uint64_t calc_reading(uint32_t high, uint32_t low) {

    return ((uint64_t)high << 32) | low;

}
