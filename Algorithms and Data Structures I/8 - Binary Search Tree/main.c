#include <stdio.h>
#include "bst.h"

int main(){
    bstree_t *t = bstreeCreate(); 

    bstreeInsert(&t->root, 5);
    bstreeInsert(&t->root, 3);
    bstreeInsert(&t->root, 7);
    bstreeInsert(&t->root, 9);
    bstreeInsert(&t->root, 8);
    bstreeInsert(&t->root, 2);
    bstreePrint(t->root);
    printf("\n");
    bstreePrintPreorder(t->root);
    printf("\n");
    bstreePrintInorder(t->root);
    printf("\n");
    bstreePrintPostorder(t->root);
    printf("\n");
    bstreeDestroy(t->root);
    return 0;
}