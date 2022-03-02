/*
 * invalid_logfile.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for invalid_logfile
 *
 */

#include "log_mgr.hpp"

#include <stdlib.h>
#include <unistd.h>

int main() {
    int i;
    float z = 0.5;

    int file_status = set_logfile("locked_file");
    if (file_status == OK) {
        for (i = 0; i < 50; i++) {
            log_event(INFO, "[%d]This is test %d for %f", getpid(), i, z);
            log_event(WARNING, "[%d]This is test %d for %f", getpid(), i, z);
            log_event(FATAL, "[%d]This is test %d for %f", getpid(), i, z);
            z = z * 0.98;
        }

        close_logfile();
    }
    exit(file_status);
}
