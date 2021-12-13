#include "commands.h"
#include "bst.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

bool operationDecider(bstree_t *t){
    bool isEOF = FALSE;
    char *line = readLine(&isEOF);
    char *operation = strtok(line, " "); //first word is the operation
    char *infos = strtok(NULL, "\n"); //the remaining data is stored

    if (strcmp(operation, "insercao") == 0)
        entryInsert(t, infos);
    else if (strcmp(operation, "impressao") == 0)
        entryPrint(t, infos);

    free(line);
    return isEOF;
}

void entryInsert(bstree_t *t, char *infos){
    int data = strtol(infos, NULL, 10); // char* to int
    bstreeInsert(&t->root, data);
}

void entryPrint(bstree_t *t, char *infos){
    if (!bstreeEmpty(t))
    {
        if (strcmp(infos, "pre-ordem") == 0)
            bstreePrintPreorder(t->root);
        else if (strcmp(infos, "pos-ordem") == 0)
            bstreePrintPostorder(t->root);
        else
            bstreePrintInorder(t->root);
    }else
        printf("VAZIA");
    printf("\n");
}

char *readLine(bool *isEOF){
    int c,k=0;
    char *line = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    c = getchar();
    if (c == EOF) *isEOF = TRUE;
    else ungetc(c, stdin);

    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    return line;
}