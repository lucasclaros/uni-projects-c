/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 09:11
 *   Modified time: 04/11/2021 14:35
 */


#include "commands.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node { 
    type x;
    struct Node *next;
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
    node_t *curr = l->start;
    while (curr != NULL)
    {
        l->start = l->start->next;
        free(curr->x->name);
        free(curr->x);
        free(curr);
        curr = l->start;
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

    if (listisEmpty(l))
        l->start = newNode;
    else 
        l->end->next = newNode;


    l->end = newNode;
    l->sizeList++;
    return 1;
}

int listInsertbyID(list_t *l, users_t *user){
    if (l == NULL || listisFull(l)) return -1;

    node_t *prev = NULL, *newNode = listSearchElement(l, user, &prev);
    if (newNode == NULL) newNode = malloc(sizeof(node_t));
    else return 0;

    newNode->x = user;
    newNode->next = NULL;

    if(listisEmpty(l))
    {
        l->start = newNode;
        l->end = newNode;
    }
    else
    {
        node_t *nodeInsertAfter = getInsertPosition(l, user);
        if (nodeInsertAfter == NULL) // first elemnt
        {
            newNode->next = l->start;
            l->start = newNode;
        }
        else if (nodeInsertAfter->next == NULL) // last element
        {
            nodeInsertAfter->next = newNode;
            l->end = newNode;
        }
        else
        {
            newNode->next = nodeInsertAfter->next;
            nodeInsertAfter->next = newNode;
        }
    }
    l->sizeList++;
    return 1;
}

node_t *getInsertPosition(list_t *l, users_t *user){
    node_t *curr = l->start, *prev = NULL;
    while (curr != NULL)
    {
        if(curr->x->id > user->id)
            return prev;
        prev = curr;
        curr = curr->next;
    }
    return prev;
}

int listRemove(list_t *l, type x){
    if (l == NULL || listisEmpty(l)) return -1;

    node_t *prev = NULL, *nodetoRemove = listSearchElement(l, x, &prev);

    if (nodetoRemove == NULL) return 0;

    if (prev == NULL) // it's the first element
        l->start = nodetoRemove->next;
    else
        prev->next = nodetoRemove->next;

    free(nodetoRemove->x->name);
    free(nodetoRemove->x);
    free(nodetoRemove);
    l->sizeList--;
    return 1;
}

void listPrint(list_t *l){
    if (listisEmpty(l))
        printf("VAZIA");
    else
    {
        node_t *curr = l->start;
        while (curr != NULL)
        {
            printf("%d, %s; ", curr->x->id, curr->x->name);
            curr = curr->next;
        }
    }
    printf("\n");
}

node_t *listSearchElement(list_t *l, type x, node_t **prev){
    node_t *curr = l->start;
    while (curr != NULL)
    {
        if(curr->x->id == x->id)
            return curr;
        *prev = curr;
        curr = curr->next;
    }
    return NULL;
}