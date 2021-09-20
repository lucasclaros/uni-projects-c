/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/09/2021 15:50
 *   Modified time: 20/09/2021 01:13
 *   Description: 
 *      Learning about Stack with decimal to binary conversion
 */

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int read_command(int *);

int main(){
    queue_t *p = createQueue();
    int *c = malloc(SIZE_QUEUE*sizeof(int));
    for (int i = 0; i < SIZE_QUEUE; i++)
    {
        c[i] = i;
        insert(p, &c[i]);
    }
    
    while (!isEmpty(p))
    {
        void *x;
        x = remove_elem(p);
        printf("%d ", *(int *)x);
    }
    printf("\n");
    free(c);
    destroy(p);
    return 0;
}


int read_command(int *c){
    scanf(" %d", c); 
    if (*c == '0')
        return 0;
    return 1;
}
