#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    list_t *l = listCreate();
    for (int i = 0; i < 10; i++)
        listInsert(l, i);
    listPrint(l); 
    listDestroy(l);
    return 0;
}