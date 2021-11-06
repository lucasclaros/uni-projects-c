/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 09:11
 *   Modified time: 05/11/2021 05:01
 */

#include "list.h"
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

int listInsert(list_t *l, type x){
    if (l == NULL || listisFull(l)) return -1;
    
    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) return -1;

    newNode->x = x;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (!listisEmpty(l))
    {
        newNode->prev = l->end;
        l->end->next = newNode;
    }else 
        l->start = newNode;


    l->end = newNode;
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
        l->start = result->next;
        result->prev = NULL;
    }
    else if (position == LAST)
        result->prev->next = NULL;
    else 
    {
        result->prev->next = result->next;
        result->next->prev = result->prev;
    }

    free(result);
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

void listPrint(list_t *l){
    node_t *curr = l->start;
    while (curr != NULL)
    {
        printf("%d", curr->x);
        curr = curr->next;
        if (curr != NULL) printf(",");
    }
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

void listCopy(list_t *src, list_t *dest){
    node_t *curr = src->start;

    for (; curr != NULL; curr = curr->next)
        listInsert(dest, curr->x);
}

void listSumNodes(list_t *src, list_t *dest){
    if (src == NULL) return;

    if (listisEmpty(dest))
        listCopy(src, dest);
    else
    {
        node_t *src_index = src->start, *dest_index = dest->start;
        while (src_index != NULL)
        {
            if (dest_index == NULL) 
                listInsert(dest, src_index->x);
            else
            {
                dest_index->x += src_index->x; 
                dest_index = dest_index->next;
            }
                
            src_index = src_index->next;
        }
    }
}