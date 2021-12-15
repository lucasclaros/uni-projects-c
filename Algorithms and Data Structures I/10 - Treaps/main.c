#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "treap.h"

int main(){
    srand(time(NULL));
    treap_t *t = treapCreate(); 

    treapInsert(&t->root, 30, 5);
    treapInsert(&t->root, 20, 2);
    treapInsert(&t->root, 40, 4);
    treapInsert(&t->root, 70, 10);
    treapInsert(&t->root, 50, 15);
    treapInsert(&t->root, 20, 8);
    treapPrintPreorder(t->root);
    printf("\n");
    treapRemove(&t->root, 50);
    treapPrintInorder(t->root);
    printf("\n");
    treapDestroy(t->root);
    free(t);
    // treapPrintPostorder(t->root);
    // printf("\n");
    // treapDestroy(t->root);
    return 0;
}