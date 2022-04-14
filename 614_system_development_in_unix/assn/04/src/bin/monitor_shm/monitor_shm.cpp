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

void monitor(int duration, shared_array_elem* shared_array) {

    int time_elapsed = 0;

    // count of the active array elements (i.e. valid)
    int num_valid = 0;
    // the average x and y values over the active array elements
    float x_ave = 0.0, y_ave = 0.0;

    while (time_elapsed < duration) {

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

        for (int i = 0; i < shared_array_size; i++) {
            if (shared_array[i].is_valid) {
                num_valid += shared_array[i].is_valid;
                x_ave += shared_array[i].x;
                y_ave += shared_array[i].y;
            }
        }

        // prevent divide-by-zero
        if (num_valid) {
            x_ave /= num_valid;
            y_ave /= num_valid;
        }
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

    int mem_key = ftok("input_data", 1);
    shared_array_elem* shared_array =
        (shared_array_elem*)connect_shm(mem_key, 4 * sizeof(int));
    printf("key: %d\n", mem_key);

    monitor(monitor_duration, shared_array);

    detach_shm((void*)shared_array);

    return OK;
}
