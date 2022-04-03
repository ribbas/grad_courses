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
                       (void*)THREAD_NUM)) {
        printf("Error:unable to create thread: %d\n", errno);
        return THD_ERROR;
    }
    printf("crea: %d:%lu\n", THREAD_NUM, THREADS[THREAD_NUM]);

    return THREAD_NUM;
}

int th_wait(ThreadHandles thread_id) {

    printf("wait: %d:%lu\n", thread_id, THREADS[thread_id]);
    return (pthread_join(THREADS[thread_id], nullptr) == THD_OK);
}

int th_wait_all(void) {

    for (int tid = 0; tid < MAX_THREAD_NUM; tid++) {
        if (!THREADS[tid]) {
            break;
        }
        th_wait(tid);
    }
    return THD_OK;
}

int th_kill(ThreadHandles) {}

int th_kill_all(void) {}

int th_exit(void) {
    printf("exit: %d:%lu:%lu\n", THREAD_NUM, THREADS[THREAD_NUM],
           pthread_self());
    pthread_exit(nullptr);
}
