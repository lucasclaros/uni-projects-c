/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 23/10/2021 17:03
 *   Modified time: 25/10/2021 20:37
 *   Description: Image Compression - Quad Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned short ushort;
typedef enum bool { FALSE, TRUE } bool;

typedef struct Quadrant{
    int startX, startY, endX, endY;
} quadrant_t;

typedef struct Image{
    ushort **matrix, dimension;
} image_t;


ushort **readImage(int);
void rec_function(image_t *, quadrant_t *);
quadrant_t *createQuadrant(int, int, int, int);
bool checkValues(image_t *, quadrant_t *);
void printLeaves(image_t *, quadrant_t *);

int main(){
    image_t *i = malloc(sizeof(image_t));
    scanf("%hu %hu", &i->dimension, &i->dimension);

    i->matrix = readImage(i->dimension);
    quadrant_t *fullImage = createQuadrant(0, 0, (i->dimension)-1, (i->dimension)-1);

    rec_function(i, fullImage);

    for (int j = 0; j < i->dimension; j++)
        free(i->matrix[j]);
    free(i->matrix); 
    free(i);
    free(fullImage);

    return 0;
}

ushort **readImage(int dimension){
    ushort **t = malloc(dimension * sizeof(ushort *));
    assert(t != NULL);

    for (int i = 0; i < dimension; i++)
    {
        t[i] = malloc(dimension * sizeof(ushort));
        assert(t[i] != NULL);
    }
    
    for (int i=0; i < dimension; i++)
        for (int j=0; j < dimension; j++)
            scanf(" %hu", &t[i][j]);

    return t;
}

quadrant_t *createQuadrant(int startX, int startY, int endX, int endY){
    quadrant_t *q = malloc(sizeof(quadrant_t));
    assert( q != NULL );
    q->startX = startX;
    q->startY = startY;
    q->endX = endX;
    q->endY = endY;
    return q;
}

void rec_function(image_t *image, quadrant_t *quad){
    printf("-1 ");
	int centerX = (quad->startX + quad->endX) / 2;
	int centerY = (centerX-quad->startX) + quad->startY;

    if(centerX == quad->startX)
    {
        printLeaves(image, quad);
        return;
    }

    //first quadrant
    quadrant_t *northwest = createQuadrant(quad->startX, quad->startY, centerX, centerY);
    if( checkValues(image, northwest) ) printf("%hu ", image->matrix[northwest->startY][northwest->startX]);
    else rec_function(image, northwest);

    //second quadrant
    quadrant_t *northeast = createQuadrant(centerX+1, quad->startY, quad->endX, centerY);
    if( checkValues(image, northeast) ) printf("%hu ", image->matrix[northeast->startY][northeast->startX]);
    else rec_function(image, northeast);

    //third quadrant
    quadrant_t *southwest = createQuadrant(quad->startX, centerY+1, centerX, quad->endY);
    if( checkValues(image, southwest) ) printf("%hu ", image->matrix[southwest->startY][southwest->startX]);
    else rec_function(image, southwest);

    //fourth quadrant
    quadrant_t *southeast = createQuadrant(centerX+1, centerY+1, quad->endX, quad->endY);
    if( checkValues(image, southeast) ) printf("%hu ", image->matrix[southeast->startY][southeast->startX]);
    else rec_function(image, southeast);

    free(northwest);
    free(northeast);
    free(southwest);
    free(southeast);
}


bool checkValues(image_t *image, quadrant_t *quad){

    ushort lastValue = image->matrix[quad->startY][quad->startX];
    for (int i = quad->startY; i <= quad->endY; i++)
    {
        for (int j = quad->startX; j <= quad->endX; j++)
        {
            if (image->matrix[i][j] != lastValue) return FALSE;
            else lastValue = image->matrix[i][j];
        }
    }
    return TRUE;
}


void printLeaves(image_t *image, quadrant_t *quad){
    printf("%hu ", image->matrix[quad->startY][quad->startX]);
    printf("%hu ", image->matrix[quad->startY][quad->startX+1]);
    printf("%hu ", image->matrix[quad->startY+1][quad->startX]);
    printf("%hu ", image->matrix[quad->startY+1][quad->startX+1]);
}