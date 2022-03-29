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
    std::cout << "Hello World! Thread ID, " << tid << std::endl;
    th_exit();
    // return nullptr;
}

int main() {

    th_execute(PrintHello);
    th_execute(PrintHello);
    th_execute(PrintHello);
    th_execute(PrintHello);
    th_exit();

    exit(0);
}
