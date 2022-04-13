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

        printf("Invalid number of arguments provided\n");
        return ERROR;

    } else {

        std::ifstream infile(argv[1]);
        int index, time_inc;
        float x, y;

        int mem_key = ftok(argv[1], 1);
        shared_array_elem* shared_array =
            (shared_array_elem*)connect_shm(mem_key, 4 * sizeof(int));
        printf("key: %d\n", mem_key);

        init_shared_array(shared_array);

        while (infile >> index >> x >> y >> time_inc) {

            if (time_inc > -1) {

                // printf("gonna sleep for %d s\n", time_inc);
                sleep(time_inc);
                shared_array[index].is_valid = 1;
                shared_array[index].x = x;
                shared_array[index].y = y;

            } else {
                sleep(abs(time_inc));
                shared_array[index].is_valid = 0;
                // printf("not gonna sleep for %d s\n", abs(time_inc));
            }
        }

        detach_shm((void*)shared_array);
    }

    return OK;
}
