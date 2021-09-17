/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/09/2021 15:50
 *   Modified time: 17/09/2021 02:19
 *   Description: 
 *      Learning about Stack with decimal to binary conversion
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int read_command(elem *);

int main(){
    elem c;
    queue_t *p = createQueue();
    while (read_command(&c))
        insert(p, c);
    printQueue(p);
    destroy(p);
    return 0;
}


int read_command(elem *c){
    scanf(" %d", c); 
    if (*c == -1)
        return 0;
}
