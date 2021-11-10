#include "commands.h"
#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    sl_t *sl = slCreate();
    bool isEOF = FALSE;
    while (!isEOF)
    {
        isEOF = operationDecider(sl);
    } 
    slDestroy(sl);
    return 0;
}