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

#include <pthread.h>
#include <signal.h> /* for signal */

#define THD_OK 0
#define THD_ERROR -1

typedef int ThreadHandles;
typedef void* Funcptrs(void*);

extern ThreadHandles THREAD_NUM;
const unsigned int MAX_THREAD_NUM = 50;
extern pthread_t THREADS[MAX_THREAD_NUM];

ThreadHandles th_execute(Funcptrs);

int th_wait(ThreadHandles);

int th_wait_all(void);

int th_kill(ThreadHandles);

int th_kill_all(void);

int th_exit(void);

void sigint_handler(int signum);
#endif
