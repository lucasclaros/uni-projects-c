/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Course: SCC0201
 *   Create Time: 23/10/2021 17:03
 *   Modified time: 23/10/2021 17:20
 */

#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n')
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}