/*
 * shared_mem.cpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the driver for the shared_mem library
 *
 */

#include "shared_mem.hpp"

#include <cstring>
#include <errno.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

void* connect_shm(int key, int size) {

    int shm_id;
    int* shm_ptr;

    shm_id = shmget(key, size, IPC_CREAT | 0666);
    if (shm_id < 0) {
        fprintf(stderr, "shmget() (%d) %s\n", errno, strerror(errno));
        return nullptr;
    }

    // attach
    shm_ptr = (int*)shmat(shm_id, nullptr, 0);
    if (shm_ptr == (int*)-1) {
        fprintf(stderr, "shmat() (%d) %s\n", errno, strerror(errno));
        return nullptr;
    }

    return shm_ptr;
}

int detach_shm(void* addr) {
    return OK;
}

int destroy_shm(int key) {
    return OK;
}
