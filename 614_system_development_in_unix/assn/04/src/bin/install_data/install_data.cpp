/*
 * install_data.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the install_data program
 *
 */

#include "log_mgr.hpp"
#include "shared_mem.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <sys/ipc.h>
#include <unistd.h>

#define FTOK_PATH "/home/sahmed80"
#define SHM_ARRAY_SIZE 20

bool Sighup_Called = false;
bool Sigterm_Called = false;
bool Data_Installed = false;

int Mem_Key = -1;

typedef struct {
	int is_valid;
	float x;
	float y;
} Shm_Struct;

void sigterm_handler(int) {
	Sigterm_Called = true;
}

void sighup_handler(int) {
	Sighup_Called = true;
}

void sig_handle_wrapper(int sig, void (*handler)(int)) {

	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(sig, &sa, nullptr) < 0) {
		log_event(FATAL, "sigaction: (%d) %s", errno, strerror(errno));
		fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
	}
}

void init_shared_array(Shm_Struct* shm_array) {

	for (int i = 0; i < SHM_ARRAY_SIZE; i++) {
		shm_array[i].is_valid = 0;
		shm_array[i].x = 0;
		shm_array[i].y = 0;
	}
}

void install_at_index(Shm_Struct* shm_array, int index, float x, float y,
					  int time_inc) {
	if (time_inc > -1) {

		sleep(time_inc);
		shm_array[index].is_valid = 1;
		shm_array[index].x = x;
		shm_array[index].y = y;

	} else {

		sleep(abs(time_inc));
		shm_array[index].is_valid = 0;
	}
}

void post_loop() {

	if (Sighup_Called) {

		// if SIGHUP was invoked, reset the flag and return to the loop
		Sighup_Called = false;

	} else if (Sigterm_Called) {

		// if SIGTERM was invoked, destroy the shared memory segments and exit
		// the loop
		destroy_shm(Mem_Key);
		Data_Installed = true;

	} else {

		// if no signals were invoked, exit
		Data_Installed = true;
	}
}

int loop_file(char* in_file_path, Shm_Struct* shm_array) {

	std::ifstream in_file(in_file_path);
	int index, time_inc;
	float x, y;

	while (in_file >> index >> x >> y >> time_inc) {

		// if neither SIGHUP or SIGTERM were invoked
		if (!Sighup_Called && !Sigterm_Called) {

			if (index >= SHM_ARRAY_SIZE) {

				log_event(FATAL, "Invalid index found in input file");
				fprintf(stderr, "Invalid index found in input file\n");
				return ERROR;

			} else {

				// install data with valid data from file
				install_at_index(shm_array, index, x, y, time_inc);
			}

		} else {

			// reset shared memory data
			init_shared_array(shm_array);
			break;
		}
	}

	// once loop is exited, check states of flags to determine the next branch
	post_loop();

	in_file.close();
	return OK;
}

int main(int argc, char* argv[]) {

	set_logfile("install_data.log");
	sig_handle_wrapper(SIGTERM, sigterm_handler);
	sig_handle_wrapper(SIGHUP, sighup_handler);

	// if wrong number of arguments
	if (argc != 2) {

		log_event(FATAL, "Invalid number of arguments provided");
		fprintf(stderr, "Invalid number of arguments provided\n");
		return ERROR;

	} else {

		Mem_Key = ftok(FTOK_PATH, 1);
		Shm_Struct* shm_array =
			(Shm_Struct*)connect_shm(Mem_Key, sizeof(Shm_Struct));

		init_shared_array(shm_array);
		// if the installation loop was not completed
		while (!Data_Installed) {
			if (loop_file(argv[1], shm_array) == ERROR) {
				return ERROR;
			}
		}

		// if SIGTERM was invoked, the shared memory segments was already
		// destroyed
		if (!Sigterm_Called) {
			destroy_shm(Mem_Key);
		}
	}

	return OK;
}
