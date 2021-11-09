/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/11/2021 03:19
 *   Modified time: 08/11/2021 23:15
 */

#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Node { 
    type data;
    int level;
    struct Node *next, *down;
};

struct skipList { 
    int level, maxLevel, elements;
    struct Node *header; 
};


sl_t *slCreate(){
    sl_t *l = (sl_t *)malloc(sizeof(sl_t));
    if (l == NULL) return NULL;
    l->elements = 0;
    l->level = 0;
    l->maxLevel = MAX_LEVELS;
    l->header = slCreateNode(-1, 0, NULL, NULL);
    return l; 
}

void slDestroy(sl_t *l){
    node_t *layer = l->header;
    while (layer != NULL)
    {
        layer = layer->down;
        node_t *curr = l->header;
        while (curr != NULL)
        {
            l->header = l->header->next;
            free(curr);
            curr = l->header;
        }
    }
    free(l);
}

int slisEmpty(sl_t *l){
    if (l->elements == 0) return 1;
    else return 0;
}

node_t *slCreateNode(type data, int level, node_t *next, node_t *down){
    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) return NULL;

    newNode->data = data;    
    newNode->level = level;
    newNode->next = next;
    newNode->down = down;

    return newNode;
}

int flipCoin(int maxValue){
    srand(time(NULL));
    int num = (unsigned int)(rand() % maxValue);
    if ((num % 2) == 0) return 1;
    else return 0;
}


/**
 *  Sentinel runs through all layers above layer 0 (starting from each layer header)
 * checking if data of the next nodes are less than the actual value of search. Once
 * it found a greater value (or reached the end), it drops one level till level 0.
 * When level 0 is reached, search begins again. If value was found returns TRUE, 
 * otherwise returns FALSE.
 * 
 * 
 */
type slSearch(sl_t *l, type data){
    if (l == NULL) return FALSE;
    //
    node_t *sentinel = l->header;
    while (sentinel != NULL && sentinel->level != 0)
    {
        while (sentinel->next != NULL && sentinel->next->data < data)
            sentinel = sentinel->next;
        sentinel = sentinel->down; 
    }

    while (sentinel->next != NULL && sentinel->next->data < data)
        sentinel = sentinel->next;

    if (sentinel->next != NULL && sentinel->next->data == data) return sentinel->next->data; 
    else return -1;

}

/**
 *  Sentinel runs through all layers above layer 0 (starting from each layer header)
 * checking if data of the next nodes are less than the actual value of search. Once
 * it found a greater value (or reached the end), it drops one level till level 0
 * updating the node's vector that keeps track of previous node to insert the data.
 * When level 0 is reached, search begins again till find the right position to insert.
 * Thenceforth, it creates a newNode with data for each existing level adding up a new
 * level (with a new header and node) if necessary.
 * 
 * 
 */
int slInsert(sl_t *l, type data){

    node_t *sentinel = l->header;
    node_t *updates[l->maxLevel];
    int nodeLevel = 0;
    while(flipCoin(l->maxLevel) == 1) nodeLevel++;
    nodeLevel %= l->maxLevel;

    if (slisEmpty(l))
        updates[sentinel->level] = sentinel;
    else 
    {
        // check if word exist
        if (slSearch(l, data) != -1) return 0;

        while (sentinel != NULL && sentinel->level != 0)
        {
            while (sentinel->next != NULL && sentinel->next->data < data)
                sentinel = sentinel->next;
            updates[sentinel->level] = sentinel;
            sentinel = sentinel->down; 
        }
        
        while (sentinel->next != NULL && sentinel->next->data < data)
            sentinel = sentinel->next;
        updates[sentinel->level] = sentinel;
    }

    int currLevel = 0;
    while (currLevel <= nodeLevel && currLevel <= l->level)
    {
        node_t *newNode = slCreateNode(data, currLevel, NULL, NULL);
        newNode->next = updates[currLevel]->next;

        if (currLevel != 0)
            newNode->down = updates[currLevel-1]->next;

        updates[currLevel]->next = newNode;
        currLevel++;
    }
    
    if (nodeLevel > l->level)
    {
        for (int i = (l->level+1); i <= nodeLevel; i++)
        {
            node_t *newNode = slCreateNode(data, i, NULL, updates[i-1]->next);
            node_t *newHeader = slCreateNode(-1, i, newNode, l->header);
            l->header = newHeader;
            updates[i] = newHeader;
        }
        l->level = nodeLevel;
    }
    l->elements++;
    return 1;
}


int slRemove(sl_t *l, type data){
    if (slisEmpty(l) || (slSearch(l, data) == -1)) return 0;

    node_t *sentinel = l->header;
    node_t *updates[l->maxLevel];

    while (sentinel != NULL && sentinel->level != 0)
    {
        while (sentinel->next != NULL && sentinel->next->data < data)
            sentinel = sentinel->next;
        updates[sentinel->level] = sentinel;
        sentinel = sentinel->down; 
    }
    
    while (sentinel->next != NULL && sentinel->next->data < data)
        sentinel = sentinel->next;
    updates[sentinel->level] = sentinel;

    int currLevel = 0;
    while (currLevel <= l->level)
    {
        if (updates[currLevel]->next != NULL && updates[currLevel]->next->data == data)
        {
            node_t *rem = updates[currLevel]->next;
            updates[currLevel]->next = rem->next;
            free(rem);
        }
        currLevel++;
    }
    l->elements--;
    while (l->elements > 0 && l->header->next == NULL)
    {
        node_t *rem = l->header;
        l->header = l->header->down;
        l->level--;
        free(rem);
    }
    return 1; 
}