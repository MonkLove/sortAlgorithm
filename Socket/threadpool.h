#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void* pool_init(int thread_num, int max_queue_num);

int pool_add_worker(void* pool, void* (*callback)(void* arg), void* arg);

int pool_destroy(void* pool);

void* process_routine(void* arg);

#endif
