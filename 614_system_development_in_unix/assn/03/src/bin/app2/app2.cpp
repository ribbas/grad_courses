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

#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/*
 * This method utilizes setitimer and SIGALRM to implement sleep for `sec`
 * seconds. The number of seconds is a double and can therefore be fractional
 * increments of time.
 */
void sleep_sec(double sec) {

    struct itimerval new_it, old_it;
    struct sigaction catch_alarm, old_sig;

    // pass in a noop lambda as the handler
    catch_alarm.sa_handler = ([](int) {});

    // empty mask
    sigset_t empty;
    sigemptyset(&empty);
    catch_alarm.sa_mask = empty;

    // no flags
    catch_alarm.sa_flags = 0;

    if (sigaction(SIGALRM, &catch_alarm, &old_sig) < 0) {
        fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
    }

    // convert seconds to milliseconds for convenient computations
    int ms = sec * 1000;
    new_it.it_value.tv_sec = ms / 1000;
    new_it.it_value.tv_usec = 1000 * (ms % 1000);
    new_it.it_interval.tv_sec = 0;
    new_it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &new_it, &old_it) < 0) {
        fprintf(stderr, "setitimer: (%d) %s\n", errno, strerror(errno));
        return;
    };

    pause();
    if (sigaction(SIGALRM, &old_sig, nullptr) < 0) {
        fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
    }
}

/*
 * A worker method that is passed in to every spawned threads
 */
void* worker(void* _thread_id) {

    long thread_id = (long)_thread_id;

    log_event(INFO, "Thread %ld created", thread_id);
    printf("Thread %ld created\n", thread_id);

    // do nothing

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

            th_execute(worker);
            sleep_sec(delay);
        }

        // wait 5 seconds
        printf("Waiting 5 seconds...\n");
        sleep_sec(1.0);

        printf("Terminating all threads...\n");
        for (int i = 0; i < num_threads; i++) {

            printf("Terminating %d\n", i);
            th_kill(i);
            sleep_sec(1.0);
        }

        return THD_OK;
    }
}
