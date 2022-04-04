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
#include <sys/time.h> /* for setitimer */
#include <unistd.h>   /* for pause */
#include <unistd.h>

void* compute(void* _thread_id) {

    long thread_id = (long)_thread_id;

    log_event(INFO, "Thread %ld created", thread_id);

    log_event(INFO, "Thread %ld exiting", thread_id);
    th_exit();

    return nullptr;
}

void DoStuff(void) {

    printf("Timer went off.\n");
    th_execute(compute);
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

        double delay = std::atof(argv[2]);
        std::cout << "delat " << delay << '\n';
        DoStuff();

        // if user input is less than 1 or greater than 12, return ERROR
        if (delay < 0.1 || delay > 10.0) {

            printf("Invalid amount for delay provided\n");
            return ERROR;
        }

        struct itimerval it_val; /* for setting itimer */

        /* Upon SIGALRM, call DoStuff().
         * Set interval timer.  We want frequency in ms,
         * but the setitimer call needs seconds and useconds. */
        if (signal(SIGALRM, (void (*)(int))DoStuff) == SIG_ERR) {
            perror("Unable to catch SIGALRM");
            return THD_ERROR;
        }

        it_val.it_value.tv_sec = delay;
        it_val.it_value.tv_usec = (int)(delay * 1000000) % 1000000;
        it_val.it_interval = it_val.it_value;
        if (setitimer(ITIMER_REAL, &it_val, nullptr) == -1) {
            perror("error calling setitimer()");
            return THD_ERROR;
        }

        while (--num_threads) {
            pause();
        }

        th_wait_all();

        return THD_OK;
    }
}
