/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 29/09/2021 06:53
 *   Modified time: 29/09/2021 16:57
 */

#include "list.h"
#include "primeNumbers.h"
#include <stdio.h>
#include <stdlib.h>

int *readIndexes(int nIndexes){
    int *v = malloc(nIndexes * sizeof(int));
    if (v == NULL) return NULL;
    for (int i = 0; i < nIndexes; i++)
        scanf(" %d", &v[i]);
    return v;
}

void primesCalculate(list_t *l, int maxNumber){
    initiateValues(l, maxNumber);
    listRemoveMultiples(l);
}

void initiateValues(list_t *l, int maxNumber){
    for (int i = 2; i < maxNumber; i++)
        listInsert(l, i);
}

int isMultiple(int n1, int n2){
    if ((n1 % n2 == 0) && n1 != n2)
        return 1;
    return 0;
}