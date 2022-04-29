/*
 * install_and_monitor.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the install_and_monitor program
 *
 */

#include "log_mgr.hpp"
#include "shared_mem.hpp"
#include "thread_mgr.hpp"
#include <fstream>
#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>

typedef struct {
	int is_valid;
	float x;
	float y;
} shm_struct;

const int SHM_ARRAY_SIZE = 20;
shm_struct SHM_ARRAY[SHM_ARRAY_SIZE];
int MONITOR_DURATION = 30;
std::ifstream IN_FILE;

void init_shared_array() {

	for (int i = 0; i < SHM_ARRAY_SIZE; i++) {
		SHM_ARRAY[i].is_valid = 0;
		SHM_ARRAY[i].x = 0;
		SHM_ARRAY[i].y = 0;
	}
}

void* install_data(void* _thread_id) {

	long thread_id = (long)_thread_id;

	printf("install_data created with thread ID: %ld\n", thread_id);

	int index, time_inc;
	float x, y;

	while (IN_FILE >> index >> x >> y >> time_inc) {

		if (time_inc > -1) {

			sleep(time_inc);
			SHM_ARRAY[index].is_valid = 1;
			SHM_ARRAY[index].x = x;
			SHM_ARRAY[index].y = y;

		} else {
			sleep(abs(time_inc));
			SHM_ARRAY[index].is_valid = 0;
		}
	}

	th_exit();
	return nullptr;
}

void* monitor_shm(void* _thread_id) {

	long thread_id = (long)_thread_id;

	printf("monitor_shm created with thread ID: %ld\n", thread_id);

	int time_elapsed = 0;

	// count of the active array elements (i.e. valid)
	int num_valid = 0;
	// the average x and y values over the active array elements
	float x_ave = 0.0, y_ave = 0.0;

	while (time_elapsed < MONITOR_DURATION) {

		if (!num_valid) {

			printf("At time: %d: no elements are active\n", time_elapsed);

		} else {

			printf("At time: %d: %d elements are active: x = %f, y = %f\n",
				   time_elapsed, num_valid, x_ave, y_ave);
		}

		num_valid = 0;
		x_ave = 0.0;
		y_ave = 0.0;
		time_elapsed++;

		sleep(1);

		for (int i = 0; i < SHM_ARRAY_SIZE; i++) {
			if (SHM_ARRAY[i].is_valid) {
				num_valid += SHM_ARRAY[i].is_valid;
				x_ave += SHM_ARRAY[i].x;
				y_ave += SHM_ARRAY[i].y;
			}
		}

		// prevent divide-by-zero
		if (num_valid) {
			x_ave /= num_valid;
			y_ave /= num_valid;
		}
	}

	th_exit();
	return nullptr;
}

int main(int argc, char* argv[]) {

	set_logfile("install_and_monitor.log");

	// if wrong number of arguments
	if (argc > 3) {

		log_event(FATAL, "Invalid number of arguments provided");
		printf("Invalid number of arguments provided\n");
		return ERROR;

	} else if (argc == 3) {

		MONITOR_DURATION = std::stoi(argv[2]);
	}

	IN_FILE.open(argv[1]);
	init_shared_array();

	th_execute(install_data);
	th_execute(monitor_shm);
	th_wait_all();

	return OK;
}
