/*
 * cpu_measurements.h
 *
 *  Created on: Jan 22, 2017
 *      Author: sreejith
 */

#ifndef CPU_MEASUREMENTS_H
#define CPU_MEASUREMENTS_H

// For measuring syscall overhead
void measure_procedure_0arg(int iterations);
void measure_procedure_1arg(int iterations);
void measure_procedure_2arg(int iterations);
void measure_procedure_3arg(int iterations);
void measure_procedure_4arg(int iterations);
void measure_procedure_5arg(int iterations);
void measure_procedure_6arg(int iterations);
void measure_procedure_7arg(int iterations);

#endif
