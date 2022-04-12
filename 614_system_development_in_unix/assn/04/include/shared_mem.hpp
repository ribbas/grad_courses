/*
 * shared_mem.hpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the declarations for shared_mem
 *
 */

#ifndef SHMLIB_HPP
#define SHMLIB_HPP

#include "globals.hpp"

void* connect_shm(int key, int size);

int detach_shm(void* addr);

int destroy_shm(int key);

#endif // SHMLIB_HPP
