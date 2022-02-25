#include "log_mgr.hpp"

#include <cstring>
#include <ctime>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>

const char* logfile = "logfile";
int fd = 0;
const char* level_str[] = {"INFO", "WARNING", "FATAL"};
char buffer[MAX_BUF];

int log_event(Levels l, const char* fmt, ...) {

    std::time_t t = std::time(0); // get time now
    std::tm* now = std::localtime(&t);
    snprintf(buffer, 100, "%2d:%2d:%2d:%s:", now->tm_hour, now->tm_min,
             now->tm_sec, level_str[l]);

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer + strlen(buffer), MAX_BUF, fmt, args);
    perror(buffer);
    va_end(args);

    return OK;
}

int set_logfile(const char* logfile_name) {
    if ((fd = open(logfile_name, O_CREAT | O_APPEND | O_WRONLY, 0600)) < 0) {
        return ERROR;
    } else {
        close_logfile();
        logfile = logfile_name;
        return OK;
    }
}

void close_logfile(void) {
    close(fd);
}
