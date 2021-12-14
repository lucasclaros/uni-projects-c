#include <stdio.h>
#include <stdlib.h>
#include "bt.h"

void readTree(btree_t *t, int parent, int side);

int main(){
    int nodes;
    scanf("%d", &nodes); getchar(); getchar();

    btree_t *t = btreeCreate(); 
    readTree(t, -1, 0);

    int result = btreeSumNodes(t->root);

    if (result)
        printf("VERDADEIRO\n");
    else
        printf("FALSO\n"); 

    btreeDestroy(t->root);
    free(t);
    return 0;
}

/**
 *  The idea behind is to read and insert recursively according with left and
 * right values.
 * 
 * @param t: binary tree to insert 
 * @param parent: where node to insert
 * @param side: 0 - insert left, 1 - insert right
 */
void readTree(btree_t *t, int parent, int side){
    int id, value, left, right;
    if( scanf("%d %d %d %d", &id, &value, &left, &right) == EOF )
        return;
    getchar(); getchar(); 

    if (side == 0)
        btreeInsertLeft(t, value, parent);        
    else
        btreeInsertRight(t, value, parent);        


    if (left == -1 && right == -1) // base case
        return;
    else if (left != -1 && right != -1)
    {
        //check where to insert the next node
        if (left < right)
        {
            readTree(t, value, 0);
            readTree(t, value, 1);
        }else
        {
            readTree(t, value, 1);
            readTree(t, value, 0);
        }
    }else if (left == -1) // insert in one node
            readTree(t, value, 1);
    else
            readTree(t, value, 0);

}

