/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 03/10/2021 16:58
 *   Modified time: 09/10/2021 19:08
 */

#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include "stack.h"

char openingBrackets[SIZE_OPENERS] = "({[";
char closingBrackets[SIZE_OPENERS] = ")}]";

bool isaOpeningBracket(char c){
    bool result = FALSE;
    for (int i = 0; i < SIZE_OPENERS; i++)
        if(c == openingBrackets[i])
            result = TRUE;
    return result;
}

int getClosingBracketIndex(char c){
    for (int i = 0; i < SIZE_OPENERS; i++)
        if(c == closingBrackets[i])
            return i;
    return -1;
}

bool checkLastCharAdded(char c, int index){
    if(c == openingBrackets[index])
        return TRUE;
    return FALSE;
}


void checkSequence(stack_t *s){
    if(isEmpty(s))
        printf("BALANCEADO\n");
    else
        printf("NÃO BALANCEADO\n");
}

char *read_line(bool *isEOF){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r' || c == ' ') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    if (c == EOF) *isEOF = TRUE;
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

