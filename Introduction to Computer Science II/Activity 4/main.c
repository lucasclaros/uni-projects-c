#include "list.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int command;
    scanf(" %d", &command); getchar(); getchar();
    list_t *l = listCreate();
    searchvec_t *v = NULL;
    while (command != 0)
    {
        switch(command)
        {
            case 1:
            {
                char *filename = readLine();
                readWords(filename, l);
                listPrint(l);
                free(filename);
                break;
            }
            case 2:
                destroySearchVector(v);
                v = updateSearchVector(l);
                break;
            case 3:
            {
                char *word= readLine();
                if (checkSearchVector(v, l))
                    searchWord(v, word);
                free(word);
            }
                break;
            default: 
                break;
        }
        scanf(" %d", &command); getchar(); getchar(); 
    }
    
    listDestroy(l);
    destroySearchVector(v);
    return 0;
}

