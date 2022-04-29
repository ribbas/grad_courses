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

#include "globals.hpp"
#include <pthread.h>
#include <signal.h>

#define THD_OK OK
#define THD_ERROR ERROR

#define MAX_THREAD_NUM 50

typedef int ThreadHandles;
typedef void* Funcptrs(void*);

extern ThreadHandles Thread_Num;
extern ThreadHandles Last_Thread_Num;
extern pthread_t Threads[MAX_THREAD_NUM];

// function declarations
ThreadHandles th_execute(Funcptrs);

int th_wait(ThreadHandles);

int th_wait_all(void);

int th_kill(ThreadHandles);

int th_kill_all(void);

int th_exit(void);

void sigint_handler(int);

void sigquit_handler(int);

void sig_handle_wrapper(int, void (*)(int));

#endif // THREAD_MGR_HPP
