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
#include <sys/ipc.h>
#include <unistd.h>

typedef struct {
    int is_valid;
    float x;
    float y;
} shared_array_elem;

const int shared_array_size = 20;

int main(int argc, char* argv[]) {

    int monitor_duration = 30;
    int time_elapsed = 0;

    // if wrong number of arguments
    if (argc > 2) {

        printf("Invalid number of arguments provided\n");
        return ERROR;

    } else if (argc == 2) {

        monitor_duration = std::stoi(argv[1]);
    }

    int mem_key = ftok("input_data", 1);
    shared_array_elem* shared_array =
        (shared_array_elem*)connect_shm(mem_key, 4 * sizeof(int));
    printf("key: %d\n", mem_key);

    // count of the active array elements (i.e. valid)
    int num_valid = 0;
    // the average x and y values over the active array elements
    float x_ave = 0.0, y_ave = 0.0;

    while (time_elapsed < monitor_duration) {

        sleep(1);

        for (int i = 0; i < shared_array_size; i++) {
            num_valid += shared_array[i].is_valid;
            x_ave += shared_array[i].x;
            y_ave += shared_array[i].y;
        }
        x_ave /= num_valid;
        y_ave /= num_valid;

        printf("num_valid: %d, x: %f, y: %f\n", num_valid, x_ave, y_ave);

        num_valid = 0;
        x_ave = 0.0;
        y_ave = 0.0;
        time_elapsed++;
    }

    detach_shm((void*)shared_array);

    return OK;
}
