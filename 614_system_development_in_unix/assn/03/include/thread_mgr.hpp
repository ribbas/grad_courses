/*
 * thread_mgr.hpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the declarations for thread_mgr
 *
 */

#ifndef THREAD_MGR_HPP
#define THREAD_MGR_HPP

#define THD_OK 0
#define THD_ERROR -1

typedef int ThreadHandles;
typedef void* Funcptrs(void*);

ThreadHandles th_execute(Funcptrs);

int th_wait(ThreadHandles);

int th_wait_all(void);

int th_kill(ThreadHandles);

int th_kill_all(void);

int th_exit(void);

#endif
