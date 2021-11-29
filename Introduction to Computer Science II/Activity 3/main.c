#include "list.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    thread_t *mainThread = threadCreate();
    int time = 1;    
    while (!threadisEmpty(mainThread))
    {
        getProcessbyTime(mainThread, time);
        roundRobin(mainThread, time);
        time++;
    }
    threadDestroy(mainThread);
    return 0;
}