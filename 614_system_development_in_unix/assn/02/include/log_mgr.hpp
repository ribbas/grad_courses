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

#define ERROR -1
#define OK 0

typedef enum { INFO, WARNING, FATAL } Levels;

extern const char* logfile;
extern int fd;
const int MAX_BUF = 1000;
extern char buffer[MAX_BUF];
extern const char* level_str[3];

int log_event(Levels l, const char* fmt, ...);
int set_logfile(const char* logfile_name);
void close_logfile(void);

#endif
