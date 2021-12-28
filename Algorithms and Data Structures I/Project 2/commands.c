#include "commands.h"
#include "treap.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

bool operationDecider(treap_t *t){
    bool isEOF = FALSE;
    char *line = readLine(&isEOF);
    char *operation = strtok(line, " "); //first word is the operation
    char *infos = strtok(NULL, "\n"); //the remaining data is stored

    if (strcmp(operation, "insercao") == 0)
        entryInsert(t, infos);
    else if (strcmp(operation, "impressao") == 0)
        entryPrint(t, infos);
    else if (strcmp(operation, "remocao") == 0)
        entryRemove(t, infos);
    else
        entrySearch(t, infos);

    free(line);
    return isEOF;
}

void entryInsert(treap_t *t, char *infos){
    char *aux = strtok(infos, " ");
    int data = strtol(aux, NULL, 10); // char* to int
    aux = strtok(NULL, " ");
    int prio = strtol(aux, NULL, 10); 
    treapInsert(&t->root, data, prio);
}

void entryRemove(treap_t *t, char *infos){
    int data = strtol(infos, NULL, 10);
    if (treapRemove(&t->root, data) == 0)
        printf("Chave nao localizada\n");
}

void entrySearch(treap_t *t, char *infos){
    int data = strtol(infos, NULL, 10); 
    if (treapSearch(t->root, data) != NULL)
        printf("1\n");
    else
        printf("0\n");
}

void entryPrint(treap_t *t, char *infos){
    if (!treapEmpty(t))
    {
        if (strcmp(infos, "preordem") == 0)
            treapPrintPreorder(t->root);
        else if (strcmp(infos, "posordem") == 0)
            treapPrintPostorder(t->root);
        else if (strcmp(infos, "ordem") == 0)
            treapPrintInorder(t->root);
        else
            printLevelOrder(t->root);
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