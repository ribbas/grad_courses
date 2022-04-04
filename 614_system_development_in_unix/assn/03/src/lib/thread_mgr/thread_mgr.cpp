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

#include <iostream>

ThreadHandles THREAD_NUM = -1;
pthread_t THREADS[50];

ThreadHandles th_execute(Funcptrs func) {

    THREAD_NUM++;

    if (pthread_create(&THREADS[THREAD_NUM], nullptr, func,
                       (void*)(size_t)THREAD_NUM)) {

        printf("Error:unable to create thread: %d\n", errno);
        return THD_ERROR;
    }

    return THREAD_NUM;
}

int th_wait(ThreadHandles thread_id) {

    if (pthread_join(THREADS[thread_id], nullptr) == THD_OK) {

        return THD_OK;

    } else {

        return THD_ERROR;
    }
}

int th_wait_all() {

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        if (!THREADS[tid]) {
            break;
        }

        th_wait(tid);
    }

    return THD_OK;
}

int th_kill(ThreadHandles thread_id) {

    if (pthread_cancel(thread_id) == THD_OK) {

        return THD_OK;

    } else {

        return THD_ERROR;
    }
}

int th_kill_all() {

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        if (!THREADS[tid]) {
            break;
        }

        th_kill(tid);
    }

    return THD_OK;
}

int th_exit() {

    pthread_exit(nullptr);
    return THD_ERROR;
}

void sigint_handler(int signum) {

    printf("Thread %d is calling\n", pthread_self());

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {

        printf("Thread %d:%d is running\n", THREADS[tid], pthread_self());
        if (!THREADS[tid]) {
            break;
        }

        // if (THREADS[tid] != pthread_self()) {
        // }
    }
}
