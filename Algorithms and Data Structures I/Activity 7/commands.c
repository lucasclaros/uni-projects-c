#include "commands.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

void checkAction(char *name, list_t *l){
    if (strcmp(name, "INSERE") == 0)
    {
        users_t *newUser = malloc(sizeof(users_t));
        scanf(" %d", &newUser->id); getchar();
        newUser->name = read_line();
        int result = listInsertbyID(l, newUser); 
        if (result == 0) 
        {
            free(newUser->name);
            free(newUser);
            printf("INVALIDO\n");
        }
    }
    else if (strcmp(name, "REMOVE") == 0)
    {
        users_t *newUser = malloc(sizeof(users_t));
        scanf(" %d", &newUser->id); getchar();
        int result = listRemove(l, newUser);
        if (result == 0) printf("INVALIDO\n");
        free(newUser);
    }
    else
        listPrint(l);

}