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
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

// default logfile name
const char* Log_File = "logfile";

// default (invalid) file descriptor value
int FD = ERROR;

// default string names corresponding to the Levels enum
const char* LEVEL_STR[] = {"INFO", "WARNING", "FATAL"};

int log_event(Levels l, const char* fmt, ...) {

	int logfile_status;
	if (FD == ERROR) {

		logfile_status = set_logfile(Log_File);
	}

	if (logfile_status == ERROR) {

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

	int new_fd = open(logfile_name, O_CREAT | O_APPEND | O_WRONLY, 0600);

	if (new_fd < 0) {

		// file failed to open
		fprintf(stderr, "Error with file '%s': (%d) %s\n", logfile_name, errno,
				strerror(errno));
		return ERROR;

	} else {

		// close previous file descriptor
		close_logfile();

		// update descriptor and name of logfile
		FD = new_fd;
		Log_File = logfile_name;
		return OK;
	}
}

void close_logfile(void) {

	if (FD != ERROR) {

		// close the global file descriptor
		if (close(FD) < 0) {
			// file failed to open
			FD = -1;
			fprintf(stderr, "Error with file '%s': (%d) %s\n", Log_File, errno,
					strerror(errno));
		}
	} else {
		FD = -1;
	}
}
