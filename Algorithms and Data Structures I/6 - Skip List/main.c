#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    sl_t *sl = slCreate();
    int find;
    for (int i = 0; i < 256859; i++)
    {
        int num = (unsigned int)(rand() * ((i+16246)*(5465423+25))) % MAX_LEVELS;
        if ((i+1) == 256859) find = num;
        slInsert(sl, num);
    }
    slSearch(sl, find);
    slDestroy(sl);
    return 0;
}