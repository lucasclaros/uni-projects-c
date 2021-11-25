/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 09:11
 *   Modified time: 17/11/2021 20:10
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

int listCopy(list_t *src, list_t *dest){
    if (src == NULL) return 0;
    node_t *curr = src->start;

    for (; curr != NULL; curr = curr->next)
        listInsert(dest, curr->x);
    
    return 1;
}

int listCompare(list_t *l1, list_t *l2){
    node_t *sentinel_l1 = l1->start;
    node_t *sentinel_l2 = l2->start;
    while (sentinel_l1->next != NULL)
    {
        if(sentinel_l1->x != sentinel_l2->x) break;
        sentinel_l1 = sentinel_l1->next;
        sentinel_l2 = sentinel_l2->next;
    }

    if (sentinel_l1->x > sentinel_l2->x)
        return 1;
    else if(sentinel_l1->x < sentinel_l2->x)
        return 0;
    else 
        return -1;
}

list_t *listSumNodes(list_t *l1, list_t *l2){
    if (l1 == NULL) return NULL;

    node_t *sentinel_l1 = l1->end, *sentinel_l2 = l2->end, *sentinel_result = NULL;
    list_t *result = listCreate();

    if(l1->sizeList < l2->sizeList)
        listCopy(l2, result);
    else
        listCopy(l1, result);

    sentinel_result = result->end;
    int carryIn = 0;
    while (sentinel_result != NULL && sentinel_l1 != NULL && sentinel_l2 != NULL)
    {
        int sum = sentinel_l1->x + sentinel_l2->x + carryIn;
        if (sum >= 10)
        {
            sentinel_result->x = (sum-10);
            carryIn = 1;
        }else
        {
            sentinel_result->x = sum;
            carryIn = 0;
        }

        sentinel_result = sentinel_result->prev;
        sentinel_l1 = sentinel_l1->prev;
        sentinel_l2 = sentinel_l2->prev;
    }

    if(carryIn == 1)
    {
        if (sentinel_result == NULL)
        {
            node_t *newNode = malloc(sizeof(node_t));
            newNode->x = 1;
            newNode->prev = NULL;
            newNode->next = result->start;
            result->start = newNode;
        }else
            sentinel_result->x++;
    }
    return result;
}

int listGetSizelist(list_t *l){
    return l->sizeList;
}