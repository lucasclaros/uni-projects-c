#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

char *read_line(bool *isEOF){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    if (c == EOF) *isEOF = TRUE;
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}