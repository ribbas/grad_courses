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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define DEFAULT_SLEEP 1

void my_signal(int, void (*)(int));
void nullfunc(int);

void nullfunc(int sig) {}

void my_signal(int sig, void (*handler)(int)) {
    struct sigaction sigAction;
    sigset_t mymask;

    sigemptyset(&mymask);

    sigaddset(&mymask, SIGHUP);
    sigaddset(&mymask, SIGINT);
    sigaddset(&mymask, SIGQUIT);

    sigAction.sa_handler = handler;
    sigAction.sa_mask = mymask;
    sigAction.sa_flags = 0;

    if (sigaction(sig, &sigAction, NULL) < 0)
        perror("sigaction");
    return;
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
        std::cout << "delat " << delay << '\n';

        // if user input is less than 1 or greater than 12, return ERROR
        if (delay < 0.1 || delay > 10.0) {

            printf("Invalid amount for delay provided\n");
            return ERROR;
        }

        my_signal(SIGALRM, nullfunc);

        for (int i = 0; i < num_threads; i++) {

            th_execute(compute);
            alarm(delay);
            pause();
        }

        th_wait_all();

        return THD_OK;
    }
}
