/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 09:11
 *   Modified time: 12/12/2021 15:33
 */

#include "list.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node { 
    type x;
    struct Node *prev, *next;
};

struct List { 
    int sizeList;
    struct Node *start, *end; 
};

struct SearchVector {
    int shortcuts, totalElements;
    struct Node **vec;
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
        free(index->x);
        free(index);
        index = NULL;
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

int listSortInsert(list_t *l, type x){
    if (l == NULL || listisFull(l)) return -1;

    node_t *sentinel = NULL, *curr = l->start;
    while (curr != NULL && checkInsertPrio(curr->x, x))
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
    if (l == NULL) return;
    node_t *curr = l->start;
    int i = 3;
    while (curr != NULL && i > 0)
    {
        printf("%s\n", curr->x);
        curr = curr->next;
        i--;
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

searchvec_t *updateSearchVector(list_t *l){
    if (l == NULL) return NULL;

    searchvec_t *v = malloc(sizeof(searchvec_t));
    if (v == NULL) return NULL;

    v->shortcuts = 0; 
    v->totalElements = 0; 
    v->vec = malloc(26*sizeof(node_t *));
    // set all nodes to null to make search easier
    for (int i = 0; i < 26; i++)
        v->vec[i] = NULL;
    

    node_t *sentinel = l->start;
    while (sentinel != NULL)
    {
        //  [sentinel->x[0] - 'a'] maps any letter (lower case) to [0, 25] range
        v->vec[sentinel->x[0] - 'a'] = sentinel;
        v->shortcuts++;
        char lastChar = sentinel->x[0];
        while (sentinel != NULL && sentinel->x[0] == lastChar)
        {
            v->totalElements++;
            sentinel = sentinel->next;
        }
    }
    printf("%d\n", v->shortcuts);
    return v; 
}

void destroySearchVector(searchvec_t *v){
    if (v != NULL )
        free(v->vec);
    free(v);
}

void searchWord(searchvec_t *v, char *word){
    int i = 0;
    //get the corresponding start node from vector by the same mapping logic
    node_t *start = v->vec[word[0] - 'a'];
    if (start != NULL)
    {
        char lastChar = start->x[0];
        while (start != NULL && start->x[0] == lastChar)
        {
            if (strcmp(start->x, word) == 0)
            {
                printf("%d\n", i);
                return;
            }
            i++;
            start = start->next;
        }
    }
    printf("Palavra nao existe na lista.\n");
}

int checkSearchVector(searchvec_t *v, list_t *l){
    if(v != NULL && l != NULL && v->totalElements == l->sizeList)
        return 1;
    printf("Vetor de indices nao atualizado.\n");
    return 0;
}