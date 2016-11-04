/********************************************************\
**    Copyright(C)2016 All rights reserved
**
**   File Name    :    threadpool.c
**   Auther       :    Quasimodo
**   Created Time :    2016-11-03
**   Description  :
********************************************************/

#include <assert.h>
#include <pthread.h>
#include "threadpool.h"

typedef struct Worker{
    struct Worker* next;
    void*  (*callback)(void* arg);
    void*  arg;
}CThread_worker;

typedef struct Pool{
    CThread_worker* queue_head;
    pthread_t*      pthreads;
    uint32_t         thread_num;
    uint32_t         queue_size;
    uint32_t         shutdown;
    pthread_mutex_t queue_lock;
    pthread_cond_t  queue_ready;
}CThread_pool;

void* pool_init(int thread_num, int queue_size)
{
    CThread_pool* pool = NULL;
        
    pool = (CThread_pool*)malloc(sizeof(CThread_pool));
    if(NULL == pool){
        printf("Failed to malloc thread pool\n");
        return NULL;
    }
        
    pool->thread_num = thread_num;
    pool->queue_size = 0;
    pool->shutdown = 0;
    pool->queue_head = NULL;
    if(pthread_mutex_init(&(pool->queue_lock), NULL)){
        printf("Failed to init mutex\n");
        return NULL;
    }
    if(pthread_cond_init(&(pool->queue_ready), NULL)){
        printf("Failed to init condition\n");
        return NULL;
    }

	pool->pthreads = (pthread_t*)malloc(sizeof(pthread_t) * thread_num);
	if(NULL == pool->pthreads)
	{
		printf("Failed to malloc pthreads!\n");
		return NULL;
	}
    int i;
    for(i = 0; i < pool->thread_num; ++i){
        pthread_create(&pool->pthreads[i], NULL, process_routine, (void*)pool);
    }
    return (void*)pool;
}

int pool_add_worker(void* ppool, void* (*callback)(void* arg), void* arg)
{
    assert(ppool != NULL);
    assert(callback != NULL);
    assert(arg != NULL);

    CThread_pool* pool = (CThread_pool*)ppool;
    CThread_worker* newWork = (CThread_worker*)malloc(sizeof(CThread_worker));
    newWork->callback = callback;
    newWork->arg = arg;
    newWork->next = NULL;

    pthread_mutex_lock(&(pool->queue_lock));
    CThread_worker* member = pool->queue_head;
    if(member != NULL){
        while(member->next != NULL){
            member = member->next;
        }
        member->next = newWork;
    }
    else{
        pool->queue_head = newWork;
    }
    
    pool->queue_size++;
    pthread_mutex_unlock(&(pool->queue_lock));
    pthread_cond_signal(&(pool->queue_ready));
    return 0;
}

int pool_destroy(void* ptr)
{
    assert(ptr != NULL);

    CThread_pool* pool = (CThread_pool*)ptr;
    if(pool->shutdown)
        return -1;
    pool->shutdown = 1;
    pthread_cond_broadcast(&(pool->queue_ready));
    int i;
    for(i = 0; i < pool->thread_num; ++i){
        pthread_join(pool->pthreads[i], NULL);
    }
    free(pool->pthreads);

    CThread_worker* head = NULL;
    while(pool->queue_head != NULL){
        head = pool->queue_head;
        pool->queue_head = pool->queue_head->next;
        free(head);
    }
    pthread_mutex_destroy(&(pool->queue_lock));
    pthread_cond_destroy(&(pool->queue_ready));
    free(pool);
    pool = NULL;
    return 0;
}


void* process_routine(void* arg)
{
    assert(arg != NULL);

    CThread_pool* pool = (CThread_pool*)arg;
    while(1){
        pthread_mutex_lock(&(pool->queue_lock));
        while(pool->queue_size == 0 && !pool->shutdown){
            pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
        }
        if(pool->shutdown){
            pthread_mutex_unlock(&(pool->queue_lock));
            pthread_exit(NULL);
        }

        assert(pool->queue_size != 0);
        assert(pool->queue_head != NULL);
        pool->queue_size--;
        
        CThread_worker* work = pool->queue_head;
        pool->queue_head = work->next;
        pthread_mutex_unlock(&(pool->queue_lock));
        (*(work->callback))(work->arg);
        free(work);
    }
    pthread_exit(NULL);
}

#if 0
void* myprocess(void* arg)
{
    printf("thread is %d, working on task %d\n", pthread_self(), *(int*)arg);
    sleep(1);
    return NULL;
}

int main(int argc, char *argv[])
{
    void* pool = pool_init(3, 10);
    int* workingnum = (int*)malloc(sizeof(int)*10);
    int i;
    for(i = 0; i < 10; i++){
        workingnum[i] = i;
        pool_add_worker(pool, myprocess ,workingnum + i);
    }
    sleep(5);
    pool_destroy(pool);
    free(workingnum);
	return 0;
}
#endif
