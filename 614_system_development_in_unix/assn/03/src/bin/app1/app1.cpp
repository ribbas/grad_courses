/*
 * app1.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the app1 library
 *
 */

#include "log_mgr.hpp"
#include "thread_mgr.hpp"

#include <inttypes.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

void* compute(void* thread_id) {

    log_event(INFO, "Thread %ld created", thread_id);

    uint64_t num = rand();
    num = (num << 32) | rand();

    // enforce limits of value between 100000000 and 999999999
    num = (num % (4294967295 - 10000000000)) + 10000000000;

    bool is_prime = false;

    for (int i = 2; i <= num / 2; ++i) {

        // if num is divisible by i, then n is not prime
        if (!(num % i)) {
            is_prime = true;
            break;
        }
    }

    if (is_prime) {
        printf("%lu is not a prime\n", num);
    } else {
        printf("%lu is a prime\n", num);
    }

    log_event(INFO, "Thread %ld exiting", thread_id);
    th_exit();

    return nullptr;
}

int main(int argc, char* argv[]) {

    // if wrong number of arguments
    if (argc != 2) {

        printf("No arguments provided\n");
        return ERROR;

    } else {

        int num_threads = std::atoi(argv[1]);

        // if user input is less than 1 or greater than 12, return ERROR
        if (num_threads < 1 || num_threads > 12) {

            printf("Invalid number of arguments provided\n");
            return ERROR;
        }

        srand(time(nullptr));
        for (int i = 0; i < num_threads; i++) {
            th_execute(compute);
        }

        int rc = th_wait_all();

        return 0;
    }
}
