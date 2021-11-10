/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/11/2021 03:19
 *   Modified time: 10/11/2021 10:10
 */

#include "commands.h"
#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct Node { 
    type data;
    struct Node **next;
};

struct skipList { 
    int level, maxLevel;
    struct Node *header; 
};


sl_t *slCreate(){
    sl_t *sl = (sl_t *)malloc(sizeof(sl_t));
    if (sl == NULL) return NULL;
    sl->level = 0;
    sl->maxLevel = MAX_LEVELS;
    sl->header = slCreateNode(NULL, MAX_LEVELS);
    return sl; 
}

void slDestroy(sl_t *sl){
    node_t *sentinel = sl->header->next[0], *aux;
    while (sentinel != NULL)
    {
        aux = sentinel;
        sentinel = sentinel->next[0];
        entryDestroy(aux->data);
        free(aux->next);
        free(aux);
    }
    free(sl->header->next);
    free(sl->header);
    free(sl);
}

node_t *slCreateNode(type data, int level){
    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) return NULL;

    newNode->data = data;    
    newNode->next = malloc(sizeof(node_t) * (level+1));
    for (int i = 0; i < (level+1); i++)
        newNode->next[i] = NULL;
    
    return newNode;
}

int generateLevel(){

    int level = 0;
    while ((double)rand() / (double)RAND_MAX < FRACTIONS)
        level++; 

    return MIN(level, MAX_LEVELS);
}

/**
 *  Sentinel runs through all layers above layer 0 (starting from each layer upleft)
 * checking if data of the next nodes are less than the actual value of search. Once
 * it found a greater value (or reached the end), it drops one level till level 0.
 * When level 0 is reached, search begins again. If value was found returns TRUE, 
 * otherwise returns FALSE.
 * 
 * 
 */
type slSearch(sl_t *sl, type data){
    if (sl == NULL) return FALSE;

    node_t *sentinel = sl->header;
    for (int i = sl->level; i >= 0; i--)
    {
        while (sentinel->next[i] != NULL && (checkContent(sentinel->next[i]->data, data) > 0))
            sentinel = sentinel->next[i];
    }
    sentinel = sentinel->next[0];

    if (sentinel != NULL && (checkContent(sentinel->data, data) == -1)) return sentinel->data; 
    else return NULL;
}

/**
 *  Sentinel runs through all layers above layer 0 (starting from each layer upleft)
 * checking if data of the next nodes are less than the actual value of search. Once
 * it found a greater value (or reached the end), it drops one level till level 0
 * updating the node's vector that keeps track of previous node to insert the data.
 * When level 0 is reached, search begins again till find the right position to insert.
 * Thenceforth, it creates a newNode with data for each existing level adding up a new
 * level (with a new upleft and node) if necessary.
 * 
 * 
 */
int slInsert(sl_t *sl, type data){
    // check if word exist
    if (slSearch(sl, data) != NULL) return 0;

    node_t *sentinel = sl->header;

    node_t **updates = malloc((sl->maxLevel+1) * sizeof(node_t *));
    for (int i = 0; i < sl->maxLevel; i++)
        updates[i] = NULL;
    

    for (int i = sl->level; i >= 0; i--)
    {
        while (sentinel->next[i] != NULL && (checkContent(sentinel->next[i]->data, data) > 0))
            sentinel = sentinel->next[i];
        updates[i] = sentinel;
    }

    sentinel = sentinel->next[0];

    if (sentinel == NULL || (checkContent(sentinel->data, data) != 1)) 
    {
        int nodeLevel = generateLevel();
        node_t *newNode = slCreateNode(data, nodeLevel);

        if (nodeLevel > sl->level)
        {
            for (int i = (sl->level+1); i <= nodeLevel; i++)
                updates[i] = sl->header;

            sl->level = nodeLevel; 
        }

        for (int i = 0; i <= nodeLevel; i++)
        {
            newNode->next[i] = updates[i]->next[i];
            updates[i]->next[i] = newNode;
        }
    }
    free(updates);
    return 1;
}

int slRemove(sl_t *sl, type data){
    // check if word exist
    if (slSearch(sl, data) == NULL) return 0;

    node_t *sentinel = sl->header;

    node_t **updates = malloc((sl->maxLevel+1) * sizeof(node_t *));
    for (int i = 0; i < sl->maxLevel; i++)
        updates[i] = NULL;

    for (int i = sl->level; i >= 0; i--)
    {
        while (sentinel->next[i] != NULL && (checkContent(sentinel->next[i]->data, data) > 0))
            sentinel = sentinel->next[i];
        updates[i] = sentinel;
    }
    sentinel = sentinel->next[0];

    if (sentinel != NULL && (checkContent(sentinel->data, data) < 0)) 
    {
        for (int i = 0; i <= sl->level; i++)
        {
            if (updates[i]->next[i] != sentinel)
                break;
            updates[i]->next[i] = sentinel->next[i];
        }
        
        while (sl->level > 0 && sl->header->next[sl->level] == NULL)
        {
            sl->level--; 
        }

        free(sentinel->next);
        free(sentinel);
    }
    free(updates);
    return 1;
}


int slPrintWordsStartedWith(sl_t *sl, type data){
    if (sl == NULL) return 0;

    node_t *sentinel = sl->header;
    for (int i = sl->level; i >= 0; i--)
    {
        while (sentinel->next[i] != NULL && (checkFirstChar(sentinel->next[i]->data, data) > 0))
            sentinel = sentinel->next[i];
    }
    sentinel = sentinel->next[0];

    if (sentinel != NULL && (checkFirstChar(sentinel->data, data) == 0)) return 0;
    
    while (sentinel != NULL && (checkFirstChar(sentinel->data, data) < 0))
    {
        entryPrintOne(sentinel->data);
        sentinel = sentinel->next[0];
    }
    return 1;
}