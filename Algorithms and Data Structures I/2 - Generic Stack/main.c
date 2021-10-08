/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/09/2021 15:50
 *   Modified time: 03/10/2021 15:02
 *   Description: 
 *          Learning Generic Stack    
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct coordinates
{
    int x, y;
}coords_t;

int main(){

    stack_t *p = create();

    for (int i = 0; i < 10; i++)
    {
        coords_t *coords = malloc(sizeof(coords_t));
        coords->x = i;
        coords->y = 2*i;
        push(p, coords);
    }

    while (!isEmpty(p))
    {
        coords_t *coords2 = pop(p);
        printf("(%d, %d)\n", coords2->x, coords2->y);
        free(coords2);
    }
    destroy(p);
    return 0;
}
