#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int readInputs(list_t *l){

    int sizeList, nRotations;
    type value;
    scanf("%d", &sizeList);
    getchar();
    scanf("%d", &nRotations);
    getchar();

    for (int i = 0; i < sizeList; i++)
    {
        scanf("%d", &value);
        getchar();
        listInsert(l, value);
    };
    return nRotations; 
}