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
#include "log_mgr.hpp"

#include <cstring>
#include <errno.h>
#include <iostream>
#include <string>

ThreadHandles THREAD_NUM = 1;
pthread_t THREADS[MAX_THREAD_NUM] = {};

ThreadHandles th_execute(Funcptrs func) {

    THREAD_NUM++;
    if (pthread_create(&THREADS[THREAD_NUM], nullptr, func,
                       (void*)(size_t)THREAD_NUM)) {

        fprintf(stderr, "Unable to create thread '%d': (%d) %s\n", THREAD_NUM,
                errno, strerror(errno));
        return THD_ERROR;
    }

    printf("%lu made tid: %lu\n", pthread_self(), THREADS[THREAD_NUM]);

    return THREAD_NUM;
}

int th_wait(ThreadHandles thread_id) {

    if (THREADS[thread_id]) {

        if (pthread_join(THREADS[thread_id], nullptr) == THD_OK) {

            return THD_OK;

        } else {

            return THD_ERROR;
        }
    } else {
        return THD_OK;
    }
}

int th_wait_all() {

    for (int th_ix = 2; th_ix < MAX_THREAD_NUM; th_ix++) {

        if (th_wait(th_ix) == THD_ERROR) {
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_kill(ThreadHandles thread_id) {

    fprintf(stderr, "in func '%d:%lu': (%d) %s\n", thread_id,
            THREADS[thread_id], errno, strerror(errno));
    int rc;

    if (THREADS[thread_id]) {
        printf("%d exists\n", thread_id);

        if ((rc = pthread_cancel(THREADS[thread_id])) == 0) {
            printf("%d succ bruh\n", thread_id);

            return THD_OK;

        } else {
            fprintf(stderr, "pthread_cancel rc(%d) '%d': (%d) %s\n", rc,
                    thread_id, errno, strerror(errno));

            return THD_ERROR;
        }

    } else {
        printf("%d doesnt' exists\n", thread_id);

        return THD_OK;
    }
}

int th_kill_all() {

    for (int th_ix = 2; th_ix < MAX_THREAD_NUM; th_ix++) {

        if (th_kill(th_ix) == THD_ERROR) {
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_exit() {

    for (int th_ix = 2; th_ix < MAX_THREAD_NUM; th_ix++) {

        if (THREADS[th_ix] == pthread_self()) {

            log_event(INFO, "Thread %d exiting", th_ix);
            printf("Thread %d exiting\n", th_ix);
            pthread_exit(nullptr);
            break;
        }
    }
    return THD_ERROR;
}

void sigint_handler(int signum) {

    // printf("Thread %d is calling\n", CUR_THREAD_NUM);

    for (int th_ix = 2; th_ix < MAX_THREAD_NUM; th_ix++) {

        printf("Thread %lu:%lu is running\n", THREADS[th_ix], pthread_self());
        if (!THREADS[th_ix]) {
            break;
        }
    }
}

void sigquit_handler(int signum) {

    // printf("Thread %d is calling quits\n", CUR_THREAD_NUM);
    th_kill_all();
}
