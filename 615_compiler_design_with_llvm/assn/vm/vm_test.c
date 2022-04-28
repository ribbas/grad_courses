// vm_test.c
// by Professor Terrance Parr

#include "vm.h"
#include <stdio.h>
#include <time.h>

#ifndef NUM_ITERS
#define NUM_ITERS 1000
#endif

int hello[] = {
    ICONST, 1234, // 0
    PRINT,        // 1
    HALT          // 2
};

int loop[] = {
    // .GLOBALS 2; N, I
    // N = 10000            ADDRESS
    ICONST, 10000, // 0
    GSTORE, 0,     // 2
    // I = 0
    ICONST, 0, // 4
    GSTORE, 1, // 6
    // WHILE I<N:
    // START (8):
    GLOAD, 1, // 8
    GLOAD, 0, // 10
    ILT,      // 12
    BRF, 24,  // 13
    //     I = I + 1
    GLOAD, 1,  // 15
    ICONST, 1, // 17
    IADD,      // 19
    GSTORE, 1, // 20
    BR, 8,     // 22
    // DONE (24):
    // PRINT "LOOPED "+N+" TIMES."
    HALT // 24
};

const int FACTORIAL_ADDRESS = 0;
int factorial[] = {
    //                    ADDRESS
    //.def factorial: ARGS=1, LOCALS=0
    //	IF N < 2 RETURN 1
    LOAD, 0,   // 0
    ICONST, 2, // 2
    ILT,       // 4
    BRF, 10,   // 5
    ICONST, 1, // 7
    RET,       // 9
    // CONT:
    // RETURN N * FACT(N-1)
    LOAD, 0,   // 10
    LOAD, 0,   // 12
    ICONST, 1, // 14
    ISUB,      // 16
    // CALL, FACTORIAL_ADDRESS, 1, 0,    // 17
    CALL, 0, 1, 0, // 17
    IMUL,          // 21
    RET,           // 22
    // .DEF MAIN: ARGS=0, LOCALS=0
    // PRINT FACT(1)
    ICONST, 11, // 23    <-- MAIN METHOD!
    // CALL, FACTORIAL_ADDRESS, 1, 0,    // 25
    CALL, 0, 1, 0, // 25
    PRINT,         // 29
    HALT           // 30
};

static int f[] = {
    //                    ADDRESS
    // .def main() { print f(10); }
    ICONST, 10,    // 0
    CALL, 8, 1, 1, // 2
    PRINT,         // 6
    HALT,          // 7
    //.def f(x): ARGS=1, LOCALS=1
    //  a = x;
    LOAD, 0,  // 8	<-- start of f
    STORE, 1, // 10
    // return 2*a
    LOAD, 1,   // 12
    ICONST, 2, // 14
    IMUL,      // 16
    RET        // 17
};

double time_func(VM* vm, int startip, void (*f)(VM*, int, bool)) {

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    f(vm, startip, false);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    return time_spent;
}

void compute_time_ave(char* func_name, int code[], int code_size, int startip) {

    double duration = 0.0;
    fprintf(stderr, "Timing: %s() with %d iterations...\n", func_name,
            NUM_ITERS);

    VM* vm = NULL;
    vm = vm_create(code, code_size, 0);

    for (int i = 0; i < NUM_ITERS; i++) {
        duration += time_func(vm, startip, &vm_exec);
    }
    fprintf(stderr, "\tSwitch:\t\t\t%.5f\n",
            duration / (double)NUM_ITERS * 1000.0);

    duration = 0.0;
    vm_free(vm);
    vm = vm_create(code, code_size, 0);

    for (int i = 0; i < NUM_ITERS; i++) {
        duration += time_func(vm, startip, &vm_exec_goto);
    }
    fprintf(stderr, "\tComputed goto:\t%.5f\n\n",
            duration / (double)NUM_ITERS * 1000.0);
    vm_free(vm);
}

int main() {

    compute_time_ave("hello", hello, sizeof(hello), 0);
    compute_time_ave("loop", loop, sizeof(loop), 0);
    compute_time_ave("factorial", factorial, sizeof(factorial), 23);
    compute_time_ave("f", f, sizeof(f), 0);

    return 0;
}
