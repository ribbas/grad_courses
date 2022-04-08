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
#include <random>
#include <stdlib.h>

/*
 * A (purposefully inefficient) function to check if a number is prime
 */
bool is_prime(int n) {

    for (int i = 2; i <= n / 2; ++i) {

        // if n is divisible by i, then n is not prime
        if (!(n % i)) {
            return false;
        }
    }

    return true;
}

/*
 * A method to generate large random numbers
 */
uint64_t gen_large_num() {

    /* Seed */
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(
        0, 0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}

/*
 * A worker method that is passed in to every spawned threads
 */
void* worker(void* _thread_id) {

    long thread_id = (long)_thread_id;

    printf("Thread %lu created\n", thread_id);
    log_event(INFO, "Thread %lu created", thread_id);

    // keep looping until 100 primes are found
    int i = 0;
    int primes_found = 100;
    while (i < primes_found) {
        if (is_prime(gen_large_num())) {
            i++;
        }
    }

    printf("Thread %lu found 100 prime numbers\n", thread_id);
    log_event(INFO, "Thread %lu found 100 prime numbers", thread_id);
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
        while (num_threads--) {
            th_execute(worker);
        }

        th_wait_all();

        return THD_OK;
    }
}
