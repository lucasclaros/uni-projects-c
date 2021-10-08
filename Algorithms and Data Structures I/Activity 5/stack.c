#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack { 
    int top;
    elem *stack;
};

stack_t *create(){
    stack_t *p = (stack_t *)malloc(sizeof(stack_t));
    assert(p != NULL);

    p->stack = NULL;
    p->top = -1;
    return p; 
}

void destroy(stack_t *p){

    free(p->stack);
    free(p);
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

int push(stack_t *p, elem x){
    assert(p != NULL);

    if(isFull(p))
        return -1;

    p->top++;
    p->stack = (elem *)realloc(p->stack, (p->top+1) * sizeof(elem));
    assert(p->stack != NULL);
    p->stack[p->top] = x;
    return 1;
}

elem pop(stack_t *p){
    assert(p != NULL);

    if(isEmpty(p))
        return -1;

    elem x = p->stack[p->top];
    p->top--;
    p->stack = (elem *)realloc(p->stack, (p->top+1) * sizeof(elem));
    return x;
}

int top(stack_t *p, elem *x){
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;

    *x = p->stack[p->top];
    return 1;
}
