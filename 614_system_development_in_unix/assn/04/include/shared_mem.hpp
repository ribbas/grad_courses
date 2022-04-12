/*
 * shared_mem.hpp
 *
 * Sabbir Ahmed
 * System Development in the Unix Environment (605.614)
 *
 * This file contains the declarations for shared_mem
 *
 */

#ifndef SHARED_MEM_HPP
#define SHARED_MEM_HPP

#include "globals.hpp"

void* connect_shm(int key, int size);

int detach_shm(void* addr);

int destroy_shm(int key);

#endif // SHARED_MEM_HPP
