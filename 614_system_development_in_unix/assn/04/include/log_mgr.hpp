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

#include "globals.hpp"

// maximum line buffer size
#define MAX_BUF 1000

// enum of the type of line
typedef enum { INFO, WARNING, FATAL } Levels;

// string array for the corresponding Levels enum
extern const char* LEVEL_STR[3];

// name of the logfile
extern const char* Logfile;

// file descriptor of the logfile
extern int Fd;

// function declarations
int log_event(Levels, const char*, ...);

int set_logfile(const char*);

void close_logfile(void);

#endif // LOG_MGR_HPP
