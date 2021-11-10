#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    sl_t *sl = slCreate();
    int find;
    for (int i = 0; i < 3; i++)
    {
        slInsert(sl, i+1);
        slPrint(sl);
    }
    slRemove(sl, 2);
    slPrint(sl);
    slDestroy(sl);
    return 0;
}