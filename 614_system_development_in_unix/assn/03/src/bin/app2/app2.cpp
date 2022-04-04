/*
 * app2.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the app2 library
 *
 */

#include "log_mgr.hpp"
#include "thread_mgr.hpp"

#include <iostream>
#include <signal.h> /* for signal */
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h> /* for pause */

void* compute(void* _thread_id) {

    long thread_id = (long)_thread_id;

    log_event(INFO, "Thread %ld created", thread_id);

    for (int i = 0; i < 1000000; i++)
        ;

    log_event(INFO, "Thread %ld exiting", thread_id);
    th_exit();

    return nullptr;
}

int main(int argc, char* argv[]) {

    set_logfile("app2.log");

    // if wrong number of arguments
    if (argc != 3) {

        printf("Invalid number of arguments provided\n");
        return ERROR;

    } else {

        int num_threads = std::atoi(argv[1]);

        // if user input is less than 1 or greater than 12, return ERROR
        if (num_threads < 1 || num_threads > 25) {

            printf("Invalid number of threads provided\n");
            return ERROR;
        }

        int delay = std::atof(argv[2]);

        // if user input is less than 1 or greater than 12, return ERROR
        if (delay < 0.1 || delay > 10.0) {

            printf("Invalid amount for delay provided\n");
            return ERROR;
        }

        // struct itimerval it_val; /* for setting itimer */

        // /* Upon SIGALRM, call DoStuff().
        //  * Set interval timer.  We want frequency in ms,
        //  * but the setitimer call needs seconds and useconds. */
        // if (signal(SIGALRM, (void (*)(int))compute) == SIG_ERR) {
        //     perror("Unable to catch SIGALRM");
        //     exit(1);
        // }
        // it_val.it_value.tv_sec = 500 / 1000;
        // it_val.it_value.tv_usec = (500 * 1000) % 1000000;
        // it_val.it_interval = it_val.it_value;
        // if (setitimer(ITIMER_REAL, &it_val, nullptr) == -1) {
        //     perror("error calling setitimer()");
        //     exit(1);
        // }

        for (int i = 0; i < num_threads; i++) {
            th_execute(compute);
        }

        th_wait_all();

        return 0;
    }
}
