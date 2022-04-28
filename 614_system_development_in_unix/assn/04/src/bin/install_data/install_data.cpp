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

#define FTOK_PATH "/home/"

bool SIGHUP_CALLED = false;
bool SIGTERM_CALLED = false;
bool DATA_INSTALLED = false;

int MEM_KEY = -1;
const int SHM_ARRAY_SIZE = 20;

typedef struct {
    int is_valid;
    float x;
    float y;
} shm_struct;

void sigterm_handler(int) {
    SIGTERM_CALLED = true;
}

void sighup_handler(int) {
    SIGHUP_CALLED = true;
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

void init_shared_array(shm_struct* shm_array) {

    for (int i = 0; i < SHM_ARRAY_SIZE; i++) {
        shm_array[i].is_valid = 0;
        shm_array[i].x = 0;
        shm_array[i].y = 0;
    }
}

void install_at_index(shm_struct* shm_array, int index, float x, float y,
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

    if (SIGHUP_CALLED) {

        // if SIGHUP was invoked, reset the flag and return to the loop
        SIGHUP_CALLED = false;

    } else if (SIGTERM_CALLED) {

        // if SIGTERM was invoked, destroy the shared memory segments and exit
        // the loop
        destroy_shm(MEM_KEY);
        DATA_INSTALLED = true;

    } else {

        // if no signals were invoked, exit
        DATA_INSTALLED = true;
    }
}

int loop_file(char* in_file_path, shm_struct* shm_array) {

    std::ifstream in_file(in_file_path);
    int index, time_inc;
    float x, y;

    while (in_file >> index >> x >> y >> time_inc) {

        if (!SIGHUP_CALLED && !SIGTERM_CALLED) {

            if (index >= SHM_ARRAY_SIZE) {

                log_event(FATAL, "Invalid index found in input file");
                fprintf(stderr, "Invalid index found in input file\n");
                return ERROR;

            } else {

                install_at_index(shm_array, index, x, y, time_inc);
            }

        } else {

            init_shared_array(shm_array);
            break;
        }
    }

    post_loop();
    in_file.close();
    return OK;
}

int main(int argc, char* argv[]) {

    set_logfile("install_data.log");
    // sig_handle_wrapper(SIGTERM, sigterm_handler);
    // sig_handle_wrapper(SIGHUP, sighup_handler);

    sig_handle_wrapper(SIGQUIT, sigterm_handler);
    sig_handle_wrapper(SIGINT, sighup_handler);

    // if wrong number of arguments
    if (argc != 2) {

        log_event(FATAL, "Invalid number of arguments provided");
        fprintf(stderr, "Invalid number of arguments provided\n");
        return ERROR;

    } else {

        MEM_KEY = ftok(FTOK_PATH, 1);
        shm_struct* shm_array =
            (shm_struct*)connect_shm(MEM_KEY, sizeof(shm_struct));

        init_shared_array(shm_array);
        // if the installation loop was not completed
        while (!DATA_INSTALLED) {
            if (loop_file(argv[1], shm_array) == ERROR) {
                return ERROR;
            }
        }

        // if SIGTERM was invoked, the shared memory segments was already
        // destroyed
        if (!SIGTERM_CALLED) {
            destroy_shm(MEM_KEY);
        }
    }

    return OK;
}
