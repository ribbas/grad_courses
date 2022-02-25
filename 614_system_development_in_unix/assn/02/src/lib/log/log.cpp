#include "log_mgr.hpp"

#include <stdarg.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>

int log_event(Levels l, const char* fmt, ...) {
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    perror(buffer);
    va_end(args);
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
