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

ShmSeg* ShmSegs[MAX_SHM] = {};
int ShmSegCur = 0;

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

	ShmSeg* seg_data = new ShmSeg();
	seg_data->key = key;
	seg_data->addr = shm_ptr;

	ShmSegs[ShmSegCur] = seg_data;
	ShmSegCur++;

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

	for (int i = 0; i < ShmSegCur; i++) {
		if (ShmSegs[i]->key == key) {
			if (detach_shm(ShmSegs[i]->addr) == ERROR) {
				return ERROR;
			}
		}
	}

	return OK;
}
