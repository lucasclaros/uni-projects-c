#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct stack { 
    int top;
    elem stack[SIZE_STACK];
};

stack_t *create(){
    stack_t *p = (stack_t *)malloc(sizeof(stack_t));
    assert(p != NULL);
    p->top = -1;
    return p; 
}

void destroy(stack_t *p){

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

int push(stack_t *p, elem x){
    assert(p != NULL);

    if(isFull(p) == 1)
        return -1;

    p->top++;
    p->stack[p->top] = x;
    return 1;
}

int pop(stack_t *p, elem *x){
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;

    *x = p->stack[p->top];
    p->top--;
    return 1;
}

int top(stack_t *p, elem *x){
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;

    *x = p->stack[p->top];
    return 1;
}
