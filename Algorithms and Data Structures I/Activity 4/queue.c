#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

queue_t *queueCreate(){
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    assert(q != NULL);
    q->ini = 0;
    q->end = 0;
    q->total = 0;
    return q; 
}

void queueDestroy(queue_t *q){
    if(q != NULL) free(q);
}

int queueisFull(queue_t *q){
    assert(q != NULL);

    if (q->total < SIZE_QUEUE-1)
        return 0;
    return 1;
}

int queueisEmpty(queue_t *q){
    assert(q != NULL);

    if (q->total == 0)
        return 1;
    return 0;
}

int queueInsert(queue_t *q, void *x){
    assert(q != NULL);

    if(queueisFull(q) == 1)
        return -1;

    q->total++;
    q->queue[q->end] = x;
    q->end = (q->end+1) % SIZE_QUEUE;
    return 1;
}

void *queueRemove(queue_t *q){
    assert(q != NULL);
    assert(queueisEmpty(q) != 1);

    q->total--;
    void *value = q->queue[q->ini];
    q->ini = (q->ini+1) % SIZE_QUEUE;
    return value;
}