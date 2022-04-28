/*
 * install_data.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the install_data program
 *
 */

#include "shared_mem.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <sys/ipc.h>
#include <unistd.h>

#define FTOK_PATH "/home/"

int MEM_KEY = -1;
bool SIGHUP_CALLED = false;
bool DATA_INSTALLED = false;

typedef struct {
    int is_valid;
    float x;
    float y;
} shared_array_elem;

const int shared_array_size = 20;

void init_shared_array(shared_array_elem* shared_array) {

    for (int i = 0; i < shared_array_size; i++) {
        shared_array[i].is_valid = 0;
        shared_array[i].x = 0;
        shared_array[i].y = 0;
    }
}

int loop_file(std::ifstream& in_file, shared_array_elem* shared_array) {

    printf("begin\n");
    int index, time_inc;
    float x, y;

    while (in_file >> index >> x >> y >> time_inc) {

        if (!SIGHUP_CALLED) {

            if (index >= shared_array_size) {
                fprintf(stderr, "Invalid index found in input file\n");
                return ERROR;
            }

            if (time_inc > -1) {

                sleep(time_inc);
                shared_array[index].is_valid = 1;
                shared_array[index].x = x;
                shared_array[index].y = y;

            } else {
                sleep(abs(time_inc));
                shared_array[index].is_valid = 0;
            }
        } else {
            SIGHUP_CALLED = false;
            return OK;
        }
    }

    DATA_INSTALLED = true;

    return OK;
}

void sigterm_handler(int signum) {
    destroy_shm(MEM_KEY);
}

void sighup_handler(int signum) {
    SIGHUP_CALLED = true;
    printf("sighup called\n");
}

void sig_handle_wrapper(int sig, void (*handler)(int)) {

    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(sig, &sa, nullptr) < 0) {
        fprintf(stderr, "sigaction: (%d) %s\n", errno, strerror(errno));
    }
}

int main(int argc, char* argv[]) {

    // sig_handle_wrapper(SIGINT, sigterm_handler);
    sig_handle_wrapper(SIGINT, sighup_handler);

    // if wrong number of arguments
    if (argc != 2) {

        fprintf(stderr, "Invalid number of arguments provided\n");
        return ERROR;

    } else {

        std::ifstream in_file(argv[1]);

        MEM_KEY = ftok(FTOK_PATH, 1);
        shared_array_elem* shared_array =
            (shared_array_elem*)connect_shm(MEM_KEY, sizeof(shared_array_elem));

        init_shared_array(shared_array);
        while (!DATA_INSTALLED) {
            if (loop_file(in_file, shared_array) == ERROR) {
                return ERROR;
            }
        }

        destroy_shm(MEM_KEY);
    }

    return OK;
}
