/*
 * thread_mgr.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the thread_mgr library
 *
 */

#include "thread_mgr.hpp"

#include <cstring>
#include <errno.h>
#include <iostream>
#include <string>

ThreadHandles THREAD_NUM = -1;
ThreadHandles LAST_THREAD_NUM = -1;
pthread_t THREADS[MAX_THREAD_NUM] = {};

ThreadHandles th_execute(Funcptrs func) {

    // install signal handlers for SIGINT and SIGQUIT
    sig_handle_wrapper(SIGINT, sigint_handler);
    sig_handle_wrapper(SIGQUIT, sigquit_handler);

    // increment index for the threads array
    // this value is also used as the thread name
    THREAD_NUM++;
    if (pthread_create(&THREADS[THREAD_NUM], nullptr, func,
                       (void*)(size_t)THREAD_NUM)) {

        fprintf(stderr, "Unable to create thread '%d': (%d) %s\n", THREAD_NUM,
                errno, strerror(errno));
        return THD_ERROR;
    }

    // assign the last value of the global threads index to use later
    LAST_THREAD_NUM = THREAD_NUM;
    return THREAD_NUM;
}

int th_wait(ThreadHandles thread_id) {

    if (THREADS[thread_id]) {

        if (pthread_join(THREADS[thread_id], nullptr) == THD_ERROR) {

            fprintf(stderr, "Unable to join thread '%d': (%d) %s\n", thread_id,
                    errno, strerror(errno));
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_wait_all() {

    for (int th_ix = 0; th_ix < MAX_THREAD_NUM; th_ix++) {

        if (th_wait(th_ix) == THD_ERROR) {
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_kill(ThreadHandles thread_id) {

    if (THREADS[thread_id]) {

        if (pthread_cancel(THREADS[thread_id]) == THD_ERROR) {
            return THD_ERROR;
        }

        void* status;
        if (pthread_join(THREADS[thread_id], &status) == THD_ERROR) {
            fprintf(stderr, "Unable to join thread '%d': (%d) %s\n", thread_id,
                    errno, strerror(errno));
            return THD_ERROR;
        }

        if (status == (int*)THD_ERROR) {
            printf("Thread %d was killed\n", thread_id);
            THREADS[thread_id] = 0;
        }
    }

    return THD_OK;
}

int th_kill_all() {

    for (int th_ix = 0; th_ix < MAX_THREAD_NUM; th_ix++) {

        if (th_kill(th_ix) == THD_ERROR) {
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_exit() {

    for (int th_ix = 0; th_ix < MAX_THREAD_NUM; th_ix++) {

        if (THREADS[th_ix] == pthread_self()) {

            printf("Thread %d exiting\n", th_ix);
            THREADS[th_ix] = 0;
            pthread_exit(nullptr);
        }
    }

    return THD_ERROR;
}

void sigint_handler(int signum) {

    for (int th_ix = 0; th_ix < LAST_THREAD_NUM + 1; th_ix++) {

        if (!THREADS[th_ix]) {
            printf("Thread %d is dead\n", th_ix);
        } else {
            printf("Thread %d is alive\n", th_ix);
        }
    }
}

void sigquit_handler(int signum) {

    for (int th_ix = 0; th_ix < LAST_THREAD_NUM + 1; th_ix++) {

        if (THREADS[th_ix]) {

            // send SIGQUIT to all the other threads
            pthread_kill(THREADS[th_ix], SIGQUIT);
            th_kill(th_ix);
        }
    }

    pthread_exit(nullptr);
}

void sig_handle_wrapper(int sig, void (*handler)(int)) {

    struct sigaction sa;
    sigset_t mask;

    sigemptyset(&mask);

    sa.sa_handler = handler;
    sa.sa_mask = mask;
    sa.sa_flags = 0;

    if (sigaction(sig, &sa, nullptr) < 0) {
        fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
    }
}
