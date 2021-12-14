#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
    avltree_t *t = avltreeCreate(); 

    avltreeInsert(t, 5);
    avltreeInsert(t, 3);
    avltreeInsert(t, 8);
    avltreeInsert(t, 2);
    avltreeInsert(t, 7);
    avltreeInsert(t, 10);
    avltreeInsert(t, 15);
    avltreePrint(t->root);
    printf("\n");
    avltreeRemove(t, 2);
    avltreePrint(t->root);
    printf("\n");
    avltreeDestroy(t->root);
    free(t);
    return 0;
}