/*
 * test_log.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the test_log library
 *
 */

#include "thread_mgr.hpp"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

void* PrintHello(void* threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello! tid: %ld\n", tid);
    th_exit();
    return nullptr;
}

int main() {

    for (int i = 0; i < 5; i++) {
        th_execute(PrintHello);
    }
    // for (int i = 0; i < 50; i++) {
    //     int rc = th_wait(i);
    //     printf("return %d\n", rc);
    // }
    int rc = th_wait_all();

    return 0;
}
