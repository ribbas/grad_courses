/*
 * install_data.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the install_data library
 *
 */

#include "shared_mem.hpp"
#include <fstream>
#include <iostream>
#include <sys/ipc.h>
#include <unistd.h>

#define FTOK_PATH "/home/"

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

int main(int argc, char* argv[]) {

    // if wrong number of arguments
    if (argc != 2) {

        fprintf(stderr, "Invalid number of arguments provided\n");
        return ERROR;

    } else {

        std::ifstream in_file(argv[1]);
        int index, time_inc;
        float x, y;

        int mem_key = ftok(FTOK_PATH, 1);
        shared_array_elem* shared_array =
            (shared_array_elem*)connect_shm(mem_key, sizeof(shared_array_elem));

        init_shared_array(shared_array);

        while (in_file >> index >> x >> y >> time_inc) {

            if (time_inc > -1) {

                sleep(time_inc);
                shared_array[index].is_valid = 1;
                shared_array[index].x = x;
                shared_array[index].y = y;

            } else {
                sleep(abs(time_inc));
                shared_array[index].is_valid = 0;
            }
        }

        destroy_shm(mem_key);
    }

    return OK;
}
