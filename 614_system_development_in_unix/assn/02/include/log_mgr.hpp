/*
 * log_mgr.hpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the declarations for log_mgr
 *
 */

#ifndef LOG_MGR_HPP
#define LOG_MGR_HPP

// return status numbers
#define ERROR -1
#define OK 0

// maximum line buffer size
#define MAX_BUF 1000

// enum of the type of line
typedef enum { INFO, WARNING, FATAL } Levels;

// string array for the corresponding Levels enum
extern const char* level_str[3];

// name of the logfile
extern const char* logfile;

// file descriptor of the logfile
extern int fd;

// function declarations
int log_event(Levels l, const char* fmt, ...);
int set_logfile(const char* logfile_name);
void close_logfile(void);

#endif
