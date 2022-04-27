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
} shared_array_elem;

const int shared_array_size = 20;
shared_array_elem shared_array[shared_array_size];

int monitor_duration = 30;
std::ifstream in_file;

void init_shared_array(shared_array_elem* shared_array) {

    for (int i = 0; i < shared_array_size; i++) {
        shared_array[i].is_valid = 0;
        shared_array[i].x = 0;
        shared_array[i].y = 0;
    }
}

void* install_data(void* _thread_id) {

    long thread_id = (long)_thread_id;

    printf("install_data created with thread ID: %ld\n", thread_id);

    int index, time_inc;
    float x, y;

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

    return OK;
}

void* monitor_shm(void* _thread_id) {

    long thread_id = (long)_thread_id;

    printf("monitor_sleep created with thread ID: %ld\n", thread_id);

    int time_elapsed = 0;

    // count of the active array elements (i.e. valid)
    int num_valid = 0;
    // the average x and y values over the active array elements
    float x_ave = 0.0, y_ave = 0.0;

    while (time_elapsed < monitor_duration) {

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

    return OK;
}

int main(int argc, char* argv[]) {

    // if wrong number of arguments
    if (argc > 3) {

        printf("Invalid number of arguments provided\n");
        return ERROR;

    } else if (argc == 3) {

        monitor_duration = std::stoi(argv[2]);
    }

    in_file.open(argv[1]);
    init_shared_array(shared_array);

    th_execute(install_data);
    th_execute(monitor_shm);
    th_wait_all();

    return OK;
}
