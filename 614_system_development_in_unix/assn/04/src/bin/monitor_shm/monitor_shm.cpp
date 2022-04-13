/*
 * monitor_shm.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the monitor_shm library
 *
 */

#include "shared_mem.hpp"
#include <iostream>

struct shared_array_elem {
    int is_valid;
    float x;
    float y;
};

const int shared_array_size = 20;
struct shared_array_elem shared_array[shared_array_size];

void init_shared_array() {

    for (int i = 0; i < shared_array_size; i++) {
        shared_array[i].is_valid = 0;
        shared_array[i].x = 0;
        shared_array[i].y = 0;
    }
}

int main(int argc, char* argv[]) {

    int monitor_duration = 30;

    // if wrong number of arguments
    if (argc > 2) {

        printf("Invalid number of arguments provided\n");
        return ERROR;

    } else if (argc == 2) {

        monitor_duration = std::stoi(argv[1]);
    }

    return OK;
}
