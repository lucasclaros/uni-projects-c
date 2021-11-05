#include "commands.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    list_t *l = listCreate();
    char action[10];
    while (scanf("%s", action) != EOF)
    {
        getchar();
        checkAction(action, l);
    }
    listDestroy(l);
    return 0;
}