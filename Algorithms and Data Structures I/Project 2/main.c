#include "treap.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    treap_t *t = treapCreate(); 
    int commands;
    scanf("%d", &commands); getchar(); getchar();
    while (!operationDecider(t));
    treapDestroy(t->root);
    free(t);
    return 0;
}