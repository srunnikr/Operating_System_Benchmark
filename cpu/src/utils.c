/*
 * utils.c
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "utils.h"

uint64_t calc_average(uint64_t* ticks, int iterations) {

	uint64_t average = 0;

	uint64_t sum = 0;
	for(int i=0; i<iterations; ++i) {
		sum += ticks[i];
	}

	average = sum / iterations;

	return average;

}
