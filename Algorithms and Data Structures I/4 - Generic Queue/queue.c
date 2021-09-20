#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct queue { 
    int ini, end, total;
    void *queue[SIZE_QUEUE];
};

queue_t *createQueue(){
    queue_t *p = (queue_t *)malloc(sizeof(queue_t));
    assert(p != NULL);
    p->ini = 0;
    p->end = 0;
    p->total = 0;
    return p; 
}

void printQueue(queue_t *p){
    while (!isEmpty(p))
    {
        void *x;
        x = remove_elem(p);
        printf("%c ", *(char *)x);
    }
    printf("\n");
}

void destroy(queue_t *p){
    if(p != NULL) free(p);
}

int isFull(queue_t *p){
    assert(p != NULL);

    if (p->total < SIZE_QUEUE-1)
        return 0;
    return 1;
}

int isEmpty(queue_t *p){
    assert(p != NULL);

    if (p->total == 0)
        return 1;
    return 0;
}

int insert(queue_t *p, void *x){
    assert(p != NULL);

    if(isFull(p) == 1)
        return -1;

    p->total++;
    p->queue[p->end] = x;
    p->end = (p->end+1) % SIZE_QUEUE;
    return 1;
}

void *remove_elem(queue_t *p){
    assert(p != NULL);
    assert(isEmpty(p) != 1);

    p->total--;
    void *value = p->queue[p->ini];
    p->ini = (p->ini+1) % SIZE_QUEUE;
    return value;
}