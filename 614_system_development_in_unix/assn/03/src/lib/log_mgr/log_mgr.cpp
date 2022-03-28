/*
 * log_mgr.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the log_mgr library
 *
 */

#include "log_mgr.hpp"

#include <cstring>
#include <ctime>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

// default logfile name
const char* LOG_FILE = "logfile";

// default (invalid) file descriptor value
int FD = 0;

// default string names corresponding to the Levels enum
const char* LEVEL_STR[] = {"INFO", "WARNING", "FATAL"};

int log_event(Levels l, const char* fmt, ...) {

    if ((FD = open(LOG_FILE, O_CREAT | O_APPEND | O_WRONLY, 0600)) < 0) {

        // file failed to open
        return ERROR;

    } else {

        char buffer[MAX_BUF];

        // current time
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        // put hour, minute, second and Levels string into the buffer
        snprintf(buffer, 30, "%02d:%02d:%02d:%s:", now->tm_hour, now->tm_min,
                 now->tm_sec, LEVEL_STR[l]);

        // process variadic arguments with the format string
        va_list args;
        va_start(args, fmt);
        // move buffer cursor to not overwrite existing data
        vsnprintf(buffer + strlen(buffer), MAX_BUF, fmt, args);
        va_end(args);

        // append newline to buffer
        strcat(buffer, "\n");
        // write buffer to file
        write(FD, buffer, strlen(buffer));

        return OK;
    }
}

int set_logfile(const char* logfile_name) {

    if ((FD = open(logfile_name, O_CREAT | O_APPEND | O_WRONLY, 0600)) < 0) {

        // printf("%d", errno);
        // file failed to open
        return ERROR;

    } else {

        // close previous file descriptor
        close_logfile();
        // update name of logfile
        LOG_FILE = logfile_name;

        return OK;
    }
}

void close_logfile(void) {
    // close the global file descriptor
    close(FD);
}
