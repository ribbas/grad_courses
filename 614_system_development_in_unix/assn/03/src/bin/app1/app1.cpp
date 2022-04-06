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

const unsigned long LO_RANGE = 1000000000;
const unsigned long UP_RANGE = 3294967295; // 2^{32}-1 - LO_RANGE

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

    // enforce limits of value between 1000000000 and 2^{32}-1
    return (num % UP_RANGE) + LO_RANGE;
}

void* worker(void* _thread_id) {

    long thread_id = (long)_thread_id;

    printf("Thread %lu created\n", thread_id);
    log_event(INFO, "Thread %lu created", thread_id);

    int i = 0;
    int primes_found = 10;
    while (i < primes_found) {
        if (is_prime(gen_large_num())) {
            i++;
        }
    }
    printf("Thread %lu found 10 prime numbers\n", thread_id);
    log_event(INFO, "Thread %lu found 10 prime numbers", thread_id);
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
            th_execute(worker);
        }

        th_wait_all();

        return THD_OK;
    }
}
