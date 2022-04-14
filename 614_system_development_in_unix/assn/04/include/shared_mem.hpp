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

// function declarations
void* connect_shm(int, int);

int detach_shm(void*);

int destroy_shm(int);

#endif // SHARED_MEM_HPP
