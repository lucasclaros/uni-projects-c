#include <stdio.h>
#include "bt.h"

int main(){
    btree_t *t = btreeCreate(); 

    btreeInsertLeft(t, 1, -1);
    btreeInsertLeft(t, 2, 1);
    btreeInsertRight(t, 3, 1);
    btreeInsertLeft(t, 4, 3);
    btreeInsertRight(t, 5, 3);
    btreeInsertLeft(t, 6, 4);

    btreePrint(t->root);

    btreeDestroy(t->root);
    return 0;
}