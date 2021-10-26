/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 23/10/2021 17:03
 *   Modified time: 23/10/2021 18:41
 *   Description: Image Compression - Quad Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Image{
    int **image;
    int dimension, startX, startY, endX, endY;
} image_t;

typedef unsigned short usint;
typedef enum bool { FALSE, TRUE } bool;

void readImage(image_t *);
void rec_function(image_t *);
void updateLimitsX(image_t *, int, int);
void updateLimitsY(image_t *, int, int);
bool checkValues(image_t *);
void printLeaves(image_t *);

int main(){
    image_t *i = malloc(sizeof(image_t));
    assert(i != NULL);

    scanf("%d %d", &i->dimension, &i->dimension);
    readImage(i);

    updateLimitsX(i, 0, (i->dimension-1));
    updateLimitsY(i, 0, (i->dimension-1));
    printf("-1 ");
    rec_function(i);
    return 0;
}

void readImage(image_t *t){
    t->image = malloc(t->dimension * sizeof(int *));
    assert(t->image != NULL);

    for (int i = 0; i < t->dimension; i++)
    {
        t->image[i] = malloc(t->dimension * sizeof(int));
        assert(t->image[i] != NULL);
    }
    
    for (int i=0; i < t->dimension; i++)
        for (int j=0; j < t->dimension; j++)
            scanf(" %d", &t->image[i][j]);
}

void updateLimitsX(image_t *t, int start, int end){
    t->startX = start;
    t->endX = end;
}

void updateLimitsY(image_t *t, int start, int end){
    t->startY = start;
    t->endY = end;
}

void rec_function(image_t *t){
	int center = (t->startX + t->endX) / 2;

    if(center == t->startX && center == t->startY)
    {
        printLeaves(t);
        return;
    }


    //first quadrant
    updateLimitsX(t, 0, center);
    updateLimitsY(t, 0, center);
    if( checkValues(t) ) printf("%d ", t->image[t->startY][t->startX]);
    else rec_function(t);

    //second quadrant
    updateLimitsX(t, center+1, t->dimension-1);
    updateLimitsY(t, 0, center);
    if( checkValues(t) ) printf("%d ", t->image[t->startY][t->startX]);
    else rec_function(t);

    //third quadrant
    updateLimitsX(t, 0, center);
    updateLimitsY(t, center+1, t->dimension-1);
    if( checkValues(t) ) printf("%d ", t->image[t->startY][t->startX]);
    else rec_function(t);

    //fourth quadrant
    updateLimitsX(t, center+1, t->dimension-1);
    updateLimitsY(t, center+1, t->dimension-1);
    if( checkValues(t) ) printf("%d ", t->image[t->startY][t->startX]);
    else rec_function(t);

}


bool checkValues(image_t *t){

    int temp = t->image[t->startY][t->startX];
    for (int i = t->startY; i <= t->endY; i++)
    {
        for (int j = t->startX; j <= t->endX; j++)
        {
            if (t->image[i][j] != temp) return FALSE;
            else temp = t->image[i][j];
        }
    }
    return TRUE;
}


void printLeaves(image_t *t){
    printf("-1 ");
    printf("%d ", t->image[t->startY][t->startX]);
    printf("%d ", t->image[t->startY][t->startX+1]);
    printf("%d ", t->image[t->startY+1][t->startX]);
    printf("%d ", t->image[t->startY+1][t->startX+1]);
}