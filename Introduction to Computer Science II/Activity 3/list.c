/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 09:11
 *   Modified time: 29/11/2021 15:23
 */

#include "list.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

struct Node { 
    type x;
    struct Node *prev, *next;
};

struct List { 
    int sizeList;
    struct Node *start, *end; 
};


list_t *listCreate(){
    list_t *l = (list_t *)malloc(sizeof(list_t));
    if (l == NULL) return NULL;

    l->sizeList = 0;
    l->start = NULL;
    l->end = NULL;
    return l; 
}

void listDestroy(list_t *l){
    node_t *index = l->start;
    while (index != NULL)
    {
        l->start = l->start->next;
        processDestroy(index->x);
        free(index);
        index = l->start;
    }
    free(l);
}

int listisFull(list_t *l){
    if (l == NULL) return -1;

    if (l->sizeList == MAX_SIZE_LIST)
        return 1;
    return 0;
}

int listisEmpty(list_t *l){
    if (l == NULL) return -1;

    if (l->sizeList == 0)
        return 1;
    return 0;
}

int listSortInsert(list_t *l, type x){
    if (l == NULL || listisFull(l)) return -1;

    node_t *sentinel = NULL, *curr = l->start;
    while (curr != NULL && checkInsertPriority(curr->x, x))
    {
        sentinel = curr;
        curr = curr->next;
    }
    node_t *newNode = malloc(sizeof(node_t));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->x = x;
    
    if(sentinel == NULL) //insert at the start
    {
        if(curr == NULL) //empty list
        {
            l->start = newNode;
            l->end = newNode;
        }else
        {
            newNode->next = l->start;
            l->start = newNode;
        }
    }else
    {
        if (curr == NULL) //insert at the end
        {
            sentinel->next = newNode;
            l->end = newNode;
        }else
        {
            newNode->next = sentinel->next;
            sentinel->next = newNode;
        }
    }
    l->sizeList++;
    return 1;    
}

int listInsertbyPrio(list_t *l, type x){
    if (l == NULL || listisFull(l)) return -1;

    node_t *sentinel = NULL, *curr = l->start;
    while (curr != NULL && checkPriority(curr->x, x))
    {
        sentinel = curr;
        curr = curr->next;
    }
    node_t *newNode = malloc(sizeof(node_t));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->x = x;
    
    if(sentinel == NULL) //insert at the start
    {
        if(curr == NULL) //empty list
        {
            l->start = newNode;
            l->end = newNode;
        }else
        {
            newNode->next = l->start;
            l->start->prev = newNode;
            l->start = newNode;
        }
    }else
    {
        if (curr == NULL) //insert at the end
        {
            sentinel->next = newNode;
            newNode->prev = sentinel;
            l->end = newNode;
        }else
        {
            newNode->prev = sentinel;
            newNode->next = sentinel->next;
            sentinel->next->prev = newNode;
            sentinel->next = newNode;
        }
    }
    l->sizeList++;
    return 1;    
}

int listRemove(list_t *l, type x){
    if (l == NULL || listisEmpty(l)) return -1;

    node_t *result = listSearchElement(l, x);
    if (result == NULL) return -2;

    int position = listElementPosition(result);

    if (position == FIRST)
    {
        if(result->next != NULL) result->next->prev = NULL;
        l->start = result->next;
    }
    else if (position == LAST)
        result->prev->next = NULL;
    else 
    {
        result->prev->next = result->next;
        result->next->prev = result->prev;
    }

    free(result);
    result = NULL;
    l->sizeList--;
    return 1;
}

int listElementPosition(node_t *n){
    if (n->prev == NULL)
        return FIRST;
    else if (n->next == NULL)
        return LAST;
    else
        return MIDDLE;
}

node_t *listSearchElement(list_t *l, type x){
    node_t *index = l->start, *result;
    while (index != NULL)
    {
        if(index->x == x)
        {
            result = index;
            return result;
        }
        index = index->next;
    }
    return NULL;
}

type pop(list_t *l){
    if(l == NULL || l->start == NULL)
        return NULL;

    type data = l->start->x;
    node_t *aux = l->start;
    l->start = l->start->next;
    free(aux);
    l->sizeList--;
    return data;
}

type top(list_t *l){
    if (l->start != NULL)
        return l->start->x;
    return NULL;
}

void roundRobin(thread_t *t, int time){
    list_t *l = getMainProcesses(t);
    node_t *currProcess = getCurrProcess(t);
    updateCurrProcess(t);
    if(l->start != NULL && decreaseQuantum(currProcess->x))
    {
        printf("%d\n", time);
        processDestroy(currProcess->x);
        listRemove(l, currProcess->x);
        processKilled(t);
    }
}

node_t *listNextItem(node_t *n){
    return n->next;
}