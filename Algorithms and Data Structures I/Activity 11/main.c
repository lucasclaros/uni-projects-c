#include "bst.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    bstree_t *t = bstreeCreate(); 
    while (!operationDecider(t));
    bstreeDestroy(t->root);
    free(t);
    return 0;
}