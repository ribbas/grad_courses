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

typedef struct {
	int key;
	void* addr;
} SHMEM_SEG;

SHMEM_SEG* SHMEM_SEGS[50] = {};
int SHMEM_SEGS_CUR = 0;

void* connect_shm(int key, int size) {

	int shm_id;
	void* shm_ptr;

	if ((shm_id = shmget(key, size, IPC_CREAT | 0666)) < 0) {
		fprintf(stderr, "shmget() (%d) %s\n", errno, strerror(errno));
		return nullptr;
	}

	// attach
	shm_ptr = shmat(shm_id, nullptr, 0);
	if (shm_ptr == (int*)-1) {
		fprintf(stderr, "shmat() (%d) %s\n", errno, strerror(errno));
		return nullptr;
	}

	SHMEM_SEG* seg_data = new SHMEM_SEG();
	seg_data->key = key;
	seg_data->addr = shm_ptr;

	SHMEM_SEGS[SHMEM_SEGS_CUR] = seg_data;
	SHMEM_SEGS_CUR++;

	return shm_ptr;
}

int detach_shm(void* addr) {

	if (shmdt(addr) == -1) {

		fprintf(stderr, "shmdt() (%d) %s\n", errno, strerror(errno));
		return ERROR;

	} else {
		return OK;
	}
}

int destroy_shm(int key) {

	for (int i = 0; i < SHMEM_SEGS_CUR; i++) {
		if (SHMEM_SEGS[i]->key == key) {
			if (detach_shm(SHMEM_SEGS[i]->addr) == ERROR) {
				return ERROR;
			}
		}
	}

	return OK;
}
