#include <stdio.h>
#include <stdlib.h>
#include "bt.h"

void readTree(btree_t *t, int parent, int side);

int main(){
    int nodes, id, value, left, right;
    scanf("%d", &nodes); getchar(); 
    // getchar();
    btree_t *t = btreeCreate(); 
    readTree(t, -1, 0);
    // btreePrint(t->root);
    int result = btreeSumNodes(t->root);
    // printf("\n%d\n", result);
    if (result)
        printf("VERDADEIRO\n");
    else
        printf("FALSO\n"); 
    btreeDestroy(t->root);
    free(t);
    return 0;
}

void readTree(btree_t *t, int parent, int side){
    int id, value, left, right;
    if( scanf("%d %d %d %d", &id, &value, &left, &right) == EOF )
        return;
    // getchar(); 
    getchar(); 
    if (side == 0)
        btreeInsertLeft(t, value, parent);        
    else
        btreeInsertRight(t, value, parent);        

    // if (left == -1)
    // {
    //     if (right == -1)
    //         return;
    //     else
    //         readTree(t, value, 1);
    // }else readTree(t, value, 0);

    // if (right == -1)
    //     return;
    // else
    //     readTree(t, value, 1);
    if (left != -1)
    {
        if (right == -1)
            readTree(t, value, 0);
        else if (left < right)
            readTree(t, value, 0);
        else
            readTree(t, value, 1);
    }
    if (right != -1)
        readTree(t, value, 1);
}

// 100(  99(   98(   97(  96(96(NULL,NULL),NULL),  1(1(NULL,NULL),  1(NULL,NULL)))   ,1(NULL,NULL))    ,1(NULL,NULL)  ),    1(NULL,NULL) )