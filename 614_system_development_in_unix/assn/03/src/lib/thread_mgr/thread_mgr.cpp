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

ThreadHandles THREAD_NUM = 1;

pthread_t THREADS[50];

ThreadHandles th_execute(Funcptrs func) {
    THREAD_NUM++;
    int rc =
        pthread_create(&THREADS[THREAD_NUM], nullptr, func, (void*)THREAD_NUM);

    if (rc) {
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
    } else {
    }
    std::cout << "num: " << THREAD_NUM << '\n';

    // pthread_exit(nullptr);

    return THREAD_NUM;
}

int th_wait(ThreadHandles) {}

int th_wait_all(void) {}

int th_kill(ThreadHandles) {}

int th_kill_all(void) {}

int th_exit(void) {
    std::cout << "thread ID " << THREAD_NUM << ":" << pthread_self() << "\n";
    pthread_exit(nullptr);
}
