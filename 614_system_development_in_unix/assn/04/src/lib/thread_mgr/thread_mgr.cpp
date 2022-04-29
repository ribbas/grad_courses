/*
 * thread_mgr.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the thread_mgr library
 *
 */

#include "thread_mgr.hpp"

#include <cstring>
#include <errno.h>
#include <iostream>
#include <string>

ThreadHandles Thread_Num = -1;
ThreadHandles Last_Thread_Num = -1;
pthread_t Threads[MAX_THREAD_NUM] = {};

ThreadHandles th_execute(Funcptrs func) {

	// install signal handlers for SIGINT and SIGQUIT
	sig_handle_wrapper(SIGINT, sigint_handler);
	sig_handle_wrapper(SIGQUIT, sigquit_handler);

	// increment index for the threads array
	// this value is also used as the thread name
	Thread_Num++;
	if (pthread_create(&Threads[Thread_Num], nullptr, func,
					   (void*)(size_t)Thread_Num)) {

		fprintf(stderr, "Unable to create thread '%d': (%d) %s\n", Thread_Num,
				errno, strerror(errno));
		return THD_ERROR;
	}

	// assign the last value of the global threads index to use later
	Last_Thread_Num = Thread_Num;
	return Thread_Num;
}

int th_wait(ThreadHandles thread_id) {

	if (thread_id > 0 && Threads[thread_id]) {

		if (pthread_join(Threads[thread_id], nullptr) == THD_ERROR) {

			fprintf(stderr, "Unable to join thread '%d': (%d) %s\n", thread_id,
					errno, strerror(errno));
			return THD_ERROR;
		}
	}

	return THD_OK;
}

int th_wait_all() {

	for (int th_ix = 0; th_ix < MAX_THREAD_NUM; th_ix++) {

		if (th_wait(th_ix) == THD_ERROR) {
			return THD_ERROR;
		}
	}

	return THD_OK;
}

int th_kill(ThreadHandles thread_id) {

	if (thread_id > 0 && Threads[thread_id]) {

		if (pthread_cancel(Threads[thread_id]) == THD_ERROR) {
			return THD_ERROR;
		}

		th_wait(Threads[thread_id]);
	}

	return THD_OK;
}

int th_kill_all() {

	for (int th_ix = 0; th_ix < MAX_THREAD_NUM; th_ix++) {

		if (th_kill(th_ix) == THD_ERROR) {
			return THD_ERROR;
		}
	}

	return THD_OK;
}

int th_exit() {

	for (int th_ix = 0; th_ix < MAX_THREAD_NUM; th_ix++) {

		if (Threads[th_ix] == pthread_self()) {

			printf("Thread %d exiting\n", th_ix);
			Threads[th_ix] = 0;
			pthread_exit(nullptr);
		}
	}

	return THD_ERROR;
}

void sigint_handler(int signum) {

	for (int th_ix = 0; th_ix < Last_Thread_Num + 1; th_ix++) {

		if (!Threads[th_ix]) {
			printf("Thread %d is dead\n", th_ix);
		} else {
			printf("Thread %d is alive\n", th_ix);
		}
	}
}

void sigquit_handler(int signum) {

	for (int th_ix = 0; th_ix < Last_Thread_Num + 1; th_ix++) {

		if (Threads[th_ix]) {

			// send SIGQUIT to all the other threads
			pthread_kill(Threads[th_ix], SIGQUIT);
			th_kill(th_ix);
		}
	}
}

void sig_handle_wrapper(int sig, void (*handler)(int)) {

	struct sigaction sa;
	sigset_t mask;

	sigemptyset(&mask);

	sa.sa_handler = handler;
	sa.sa_mask = mask;
	sa.sa_flags = 0;

	if (sigaction(sig, &sa, nullptr) < 0) {
		fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
	}
}
