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

bool is_prime(int n) {

    for (int i = 2; i <= n / 2; ++i) {

        // if n is divisible by i, then n is not prime
        if (!(n % i)) {
            return false;
        }
    }

    return true;
}

uint64_t gen_large_num() {
    uint64_t num = rand();
    num = (num << 32) | rand();

    // enforce limits of value between 100000000 and 999999999
    return (num % (4294967295 - 10000000000)) + 10000000000;
}

void* compute(void* _thread_id) {

    long thread_id = (long)_thread_id;

    log_event(INFO, "Thread %ld created", thread_id);

    int i = MAX_THREAD_NUM;
    int primes_found = 0;

    while (--i) {

        uint64_t num = gen_large_num();

        if (is_prime(num)) {
            printf("Thread %ld: %lu -> prime\n", thread_id, num);
            primes_found++;
        } else {
            printf("Thread %ld: %lu -> non-prime\n", thread_id, num);
        }
    }

    log_event(INFO, "Thread %ld found %d prime numbers", thread_id,
              primes_found);
    log_event(INFO, "Thread %ld exiting", thread_id);
    th_exit();

    return nullptr;
}

int main(int argc, char* argv[]) {

    set_logfile("app1.log");

    // if wrong number of arguments
    if (argc != 2) {

        printf("No arguments provided\n");
        return ERROR;

    } else {

        int num_threads = std::atoi(argv[1]);

        // if user input is less than 1 or greater than 12, return ERROR
        if (num_threads < 1 || num_threads > 12) {

            printf("Invalid argument provided\n");
            return ERROR;
        }

        srand(time(nullptr));
        for (int i = 0; i < num_threads; i++) {
            th_execute(compute);
        }

        th_wait_all();

        return 0;
    }
}
