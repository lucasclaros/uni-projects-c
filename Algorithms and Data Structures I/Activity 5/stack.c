#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack { 
    int top;
    void **stack;
    int elementSize;
};

stack_t *create(int elementSize){
    stack_t *p = (stack_t *)malloc(sizeof(stack_t));
    assert(p != NULL);

    p->stack = (void **)malloc(sizeof(void *) * SIZE_STACK);
    assert(p->stack != NULL);

    p->top = -1;
    p->elementSize = elementSize;

    return p; 
}

void destroy(stack_t *p){

    while (!isEmpty(p))
    {
        free(p->stack[p->top]);
        p->stack[p->top] = NULL;
        p->top--;
    }
    if(p->stack != NULL) free(p->stack);
    if(p != NULL) free(p);
    p = NULL;

}

int isFull(stack_t *p){
    assert(p != NULL);

    if (p->top < SIZE_STACK-1)
        return 0;
    else
        return 1;
}

int isEmpty(stack_t *p){
    assert(p != NULL);

    if (p->top == -1)
        return 1;
    else
        return 0;
}

int push(stack_t *p, void *x){
    assert(p != NULL);

    if(isFull(p) == 1)
        return -1;

    p->top++;
    p->stack[p->top] = (void *)malloc(p->elementSize);
    assert(p->stack[p->top] != NULL);

    memcpy(p->stack[p->top], x, p->elementSize);
    return 1;
}

int pop(stack_t *p, void *x){
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;

    memcpy(x, p->stack[p->top], p->elementSize);
    free(p->stack[p->top]);
    p->top--;
    return 1;
}

int top(stack_t *p, void *x){
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;

    memcpy(x, p->stack[p->top], p->elementSize);
    return 1;
}
