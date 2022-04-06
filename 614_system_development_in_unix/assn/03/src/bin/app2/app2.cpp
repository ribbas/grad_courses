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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

pthread_mutex_t count_mutex;
void noop() {}

void sleep_sec(double sec) {

    struct itimerval new_it, old_it;
    struct sigaction catch_alarm, old_sig;

    void noop();
    sigset_t empty;
    sigemptyset(&empty);

    catch_alarm.sa_handler = (void (*)(int))noop;
    catch_alarm.sa_mask = empty;
    catch_alarm.sa_flags = 0;

    sigaction(SIGALRM, &catch_alarm, &old_sig);

    int ms = sec * 1000;
    new_it.it_value.tv_sec = ms / 1000;
    new_it.it_value.tv_usec = 1000 * (ms % 1000);
    new_it.it_interval.tv_sec = 0;
    new_it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &new_it, &old_it) < 0) {
        perror("setitimer");
        exit(1);
    };

    pause();
    sigaction(SIGALRM, &old_sig, nullptr);
}

void* worker(void* _thread_id) {

    long thread_id = (long)_thread_id;

    pthread_mutex_lock(&count_mutex);

    log_event(INFO, "Thread %ld created", thread_id);
    th_wait(thread_id);

    for (;;) {
        // do nothing
    }
    pthread_mutex_unlock(&count_mutex);

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

        for (int i = 2; i < num_threads + 2; i++) {

            th_execute(worker);
            printf("exec'd %d\n", i);
            sleep_sec(delay);
        }

        printf("gonna wait\n");
        sleep_sec(2);

        for (int i = 2; i < num_threads + 2; i++) {

            printf("KILL\n");

            th_kill(i);
            sleep_sec(1);
        }

        return THD_OK;
    }
}
