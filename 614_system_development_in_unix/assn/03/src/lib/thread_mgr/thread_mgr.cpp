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

ThreadHandles THREAD_NUM = -1;
pthread_t THREADS[MAX_THREAD_NUM] = {};

ThreadHandles th_execute(Funcptrs func) {

    THREAD_NUM++;
    if (pthread_create(&THREADS[THREAD_NUM], nullptr, func,
                       (void*)(size_t)THREAD_NUM)) {

        fprintf(stderr, "Unable to create thread '%d': (%d) %s\n", THREAD_NUM,
                errno, strerror(errno));
        return THD_ERROR;
    }

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

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        if (th_wait(tid) == THD_ERROR) {
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_kill(ThreadHandles thread_id) {

    fprintf(stderr, "pthread_cancel '%d': (%d) %s\n", thread_id, errno,
            strerror(errno));

    if (THREADS[thread_id]) {

        if (pthread_cancel(thread_id) == 0) {
            printf("%d succ bruh\n", thread_id);

            return THD_OK;

        } else {
            fprintf(stderr, "pthread_cancel '%d': (%d) %s\n", thread_id, errno,
                    strerror(errno));

            return THD_ERROR;
        }

    } else {
        return THD_OK;
    }
}

int th_kill_all() {

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        if (th_kill(tid) == THD_ERROR) {
            return THD_ERROR;
        }
    }

    return THD_OK;
}

int th_exit() {

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        if (THREADS[tid] == pthread_self()) {

            log_event(INFO, "Thread %d exiting", tid);
            printf("Thread %d exiting\n", tid);
            pthread_exit(nullptr);
            break;
        }
    }
    return THD_ERROR;
}

void sigint_handler(int signum) {

    // printf("Thread %d is calling\n", CUR_THREAD_NUM);

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        printf("Thread %lu:%lu is running\n", THREADS[tid], pthread_self());
        if (!THREADS[tid]) {
            break;
        }
    }
}

void sigquit_handler(int signum) {

    // printf("Thread %d is calling quits\n", CUR_THREAD_NUM);
    th_kill_all();
}
