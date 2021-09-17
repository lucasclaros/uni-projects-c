/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/09/2021 15:50
 *   Modified time: 17/09/2021 01:59
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

    stack_t *p = create(sizeof(coords_t));
    coords_t coords;

    for (int i = 0; i < 10; i++)
    {
        coords.x = i;
        coords.y = 2*i;
        push(p, &coords);
    }

    while (!isEmpty(p))
    {
        pop(p, &coords);
        printf("(%d, %d)\n", coords.x, coords.y);
    }
    destroy(p);
    return 0;
}
