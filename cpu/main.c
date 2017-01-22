#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "cpu_measurements.h"

int main() {

    measure_syscalls();

    measure_procedure_0arg();
    measure_procedure_1arg();
    measure_procedure_2arg();
    measure_procedure_3arg();
    measure_procedure_4arg();
    measure_procedure_5arg();
    measure_procedure_6arg();
    measure_procedure_7arg();

    return 0;

}
