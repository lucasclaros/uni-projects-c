#include "commands.h"
#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern char *strtok_r(char *, const char *, char **);

struct Entry
{
    char *word, *desc;
};


entry_t *createEntry(char *word, char *desc){
    entry_t *e = malloc(sizeof(entry_t));
    if (e == NULL) return NULL; 

    e->word = word;
    e->desc = desc;
    return e;
}

void entryDestroy(entry_t *e){
    if (e == NULL) return;
    free(e->word);
    free(e->desc);
    free(e);
}

int checkContent(entry_t *e1, entry_t *e2){
    int check = strcmp(e1->word, e2->word);
    if (check < 0) 
        return 1;
    else if (check > 0)
        return 0;
    else 
        return -1;
}

int checkFirstChar(entry_t *e1, entry_t *e2){
    int check = e1->word[0] - e2->word[0];
    if (check < 0) 
        return 1;
    else if (check > 0)
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

char *getWord(){
    int c,k=0;
    char *word = NULL;
    while((c=getchar()) != ' ' && c != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        word = realloc(word, (k+1) * sizeof(char));
        word[k++] = c;
    }
    word = realloc(word, (k+1) * sizeof(char));
    word[k] = '\0';
    return word;
}

void changeDescription(entry_t *e1, entry_t *e2){
    free(e1->desc);
    char *newDesc = malloc((strlen(e2->desc)+1) * sizeof(char));
    strcpy(newDesc, e2->desc);
    e1->desc = newDesc;
}


void entryInsert(sl_t *sl, char *infos){
    char *aux = strtok(infos, " ");
    char *word = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(word, aux);

    aux = strtok(NULL, "\n");;
    char *desc = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(desc, aux);

    entry_t *e = createEntry(word, desc);

    if (slInsert(sl, e) == 0)
    {
        printf("OPERACAO INVALIDA\n");
        free(word);
        free(desc);
        free(e);
    }
}

void entryRemove(sl_t *sl, char *infos){
    char *aux = strtok(infos, " ");
    char *word = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(word, aux);

    entry_t *e = createEntry(word, NULL);

    if (e == NULL || (slRemove(sl, e) == 0)) printf("OPERACAO INVALIDA\n");
    free(e->word);
    free(e);
}

void entryChange(sl_t *sl, char *infos){
    char *aux = strtok(infos, " ");
    char *word = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(word, aux);

    aux = strtok(NULL, "\n");
    char *newDesc = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(newDesc, aux);

    entry_t *find = createEntry(word, newDesc);
    entry_t *e = slSearch(sl, find);

    if (e != NULL) changeDescription(e, find);
    else 
    {
        printf("OPERACAO INVALIDA\n");
    }

    free(newDesc);
    free(word);
    free(find);
}

void entrySearch(sl_t *sl, char *infos){

    char *aux = strtok(infos, " ");
    char *word = malloc((strlen(aux)+1) * sizeof(char));
    strcpy(word, aux);

    entry_t *find = createEntry(word, NULL);
    entry_t *e = slSearch(sl, find);

    if (e == NULL) printf("OPERACAO INVALIDA\n");
    else entryPrintOne(e);

    free(find->word);
    free(find);
}

void entryPrintOne(entry_t *e){
    printf("%s %s\n", e->word, e->desc);
}



void entryPrintAll(sl_t *sl, char *infos){

    char *word = malloc((strlen(infos)+1) * sizeof(char));
    strcpy(word, infos);

    entry_t *e = createEntry(word, NULL);

    if (slPrintWordsStartedWith(sl, e) == 0)
        printf("NAO HA PALAVRAS INICIADAS POR %s\n", infos);

    free(word);
    free(e);
}

bool operationDecider(sl_t *sl){
    bool isEOF = FALSE;
    char *line = readLine(&isEOF);
    char *operation = strtok(line, " ");
    char *infos= strtok(NULL, "\n");

    if (strcmp(operation, "insercao") == 0)
        entryInsert(sl, infos);
    else if (strcmp(operation, "remocao") == 0)
        entryRemove(sl, infos);
    else if (strcmp(operation, "alteracao") == 0)
        entryChange(sl, infos);
    else if (strcmp(operation, "busca") == 0)
        entrySearch(sl, infos);
    else 
        entryPrintAll(sl, infos);

    free(line);
    return isEOF;
}
