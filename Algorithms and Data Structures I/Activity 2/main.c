/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 27/09/2021 00:21
 *   Modified time: 30/09/2021 00:39
 *   Description: Sieve of Eratosthenes
 */

#include "list.h"
#include "primeNumbers.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    list_t *l = listCreate();

    int nIndexes; 
    scanf("%d", &nIndexes);
    int *indexes_vector = readIndexes(nIndexes); 

    primesCalculate(l, MAX_SIZE_LIST);
    listPrint(l, indexes_vector, nIndexes);

    listDestroy(l);
    free(indexes_vector);
    return 0;
}