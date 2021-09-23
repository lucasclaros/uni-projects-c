#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int nLines, age, prio;
    scanf("%d", &nLines);
    getchar();
    char **teste = malloc(nLines * sizeof(char *));
    for (int i = 0; i < nLines; i++)
        teste[i]  = read_line();

    for (int i = 0; i < nLines; i++)
    {
        if (strcmp("SAI", teste[i]) == 0)
            printf("FILA VAZIA\n");
        else
        {
            char *aux = NULL, *name = NULL;
            aux = strtok(teste[i], " ");

            aux = strtok(NULL, " ");
            if (aux != NULL) strcpy(name, aux);

            if (aux != NULL) age = atoi(strtok(NULL, " "));

            if (aux != NULL) prio = atoi(strtok(NULL, " "));

            printf("%s %d %d", name, age, prio);
        }
    }

    for (int i = 0; i < nLines; i++)
        free(teste[i]);
    free(teste);
    return 0;
}

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

