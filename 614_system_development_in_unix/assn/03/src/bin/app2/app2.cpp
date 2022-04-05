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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void nullfunc() {}

void sleepSec(double sec) {

    struct itimerval newTV, oldTV;
    struct sigaction catchAlarm, oldSig;

    void nullfunc();
    sigset_t empty;
    sigemptyset(&empty);

    catchAlarm.sa_handler = (void (*)(int))nullfunc;
    catchAlarm.sa_mask = empty;
    catchAlarm.sa_flags = 0;

    sigaction(SIGALRM, &catchAlarm, &oldSig);

    int ms = sec * 1000;
    newTV.it_value.tv_sec = ms / 1000;
    newTV.it_value.tv_usec = 1000 * (ms % 1000);
    newTV.it_interval.tv_sec = 0;
    newTV.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &newTV, &oldTV) < 0) {
        perror("setitimer");
        exit(1);
    };

    pause();
    sigaction(SIGALRM, &oldSig, NULL);
}

void* compute(void* _thread_id) {

    long thread_id = (long)_thread_id;

    log_event(INFO, "Thread %ld created", thread_id);

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

        double delay = std::atof(argv[2]);

        // if user input is less than 1 or greater than 12, return ERROR
        if (delay < 0.1 || delay > 10.0) {

            printf("Invalid amount for delay provided\n");
            return ERROR;
        }

        for (int i = 0; i < num_threads; i++) {

            printf("AYODSDS\n");

            th_execute(compute);
            sleepSec(delay);
        }
        th_wait_all();

        sleepSec(5);

        for (int i = 0; i < num_threads; i++) {

            printf("KILL\n");

            th_kill(i);
            sleepSec(1);
        }

        return THD_OK;
    }
}
