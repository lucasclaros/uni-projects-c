#include "commands.h"
#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Entry
{
    char *name;
    int id;
};

entry_t *createEntry(char *name, int id){
    entry_t *e = malloc(sizeof(entry_t));
    if (e == NULL) return NULL; 

    e->name = name;
    e->id = id;
    return e;
}

void entryDestroy(entry_t *e){
    if (e == NULL) return;
    free(e->name);
    free(e);
}

int checkContent(entry_t *e1, entry_t *e2){
    if (e1->id < e2->id) 
        return 1;
    else if (e1->id > e2->id)
        return 0;
    else 
        return -1;
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

void entryInsert(sl_t *sl, char *infos){
    char *aux = strtok(infos, " "); //first "word" is the id
    int id = strtol(aux, NULL, 10); // char* to int

    aux = strtok(NULL, "\n"); //remaining data is the name
    char *name = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(name, aux);

    entry_t *e = createEntry(name, id);

    if (slInsert(sl, e) == 0)
    {
        printf("INVALIDO\n");
        entryDestroy(e);
    }
}

void entryRemove(sl_t *sl, char *infos){
    char *aux = strtok(infos, "\n");
    int id = strtol(aux, NULL, 10);

    entry_t *e = createEntry(NULL, id);

    if (e == NULL || (slRemove(sl, e) == 0)) printf("INVALIDO\n");
    entryDestroy(e);
}

void entryPrintOne(entry_t *e){
    printf("%d, %s; ", e->id, e->name);
}

bool operationDecider(sl_t *sl){
    bool isEOF = FALSE;
    char *line = readLine(&isEOF);
    char *operation = strtok(line, " "); //first word is the operation
    char *infos= strtok(NULL, "\n"); //the remaining data is stored

    if (strcmp(operation, "INSERE") == 0)
        entryInsert(sl, infos);
    else if (strcmp(operation, "REMOVE") == 0)
        entryRemove(sl, infos);
    else 
        slPrint(sl);

    free(line);
    return isEOF;
}
