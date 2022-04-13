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

struct {
    int is_valid;
    float x;
    float y;
} elem;

int main(int argc, char* argv[]) {

    // if wrong number of arguments
    if (argc != 2) {

        printf("Invalid number of arguments provided\n");
        return ERROR;

    } else {

        int index, time_inc;
        float x, y;
        std::ifstream infile(argv[1]);

        int mem_key = ftok(argv[1], 1);
        printf("filepath: %s key: %d ptr: %p\n", argv[1], mem_key,
               connect_shm(mem_key, 4 * sizeof(int)));

        while (infile >> index >> x >> y >> time_inc) {
            printf("file: %d %f %f %d\n", index, x, y, time_inc);
        }
    }

    return 0;
}
