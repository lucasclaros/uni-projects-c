#include "commands.h"
#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int wordStartedWith(entry_t *e1, entry_t *e2){
    if(e1->word[0] == e2->word[0]) return 1;
    else return 0;
}

int flipCoin(int maxValue){
    srand(time(NULL));
    unsigned int num = rand();
    if ((num % 2) == 0) return 1;
    else return 0;
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

char *getWord(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != ' ' && c != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

void changeDesc(entry_t *e1, entry_t *e2){
    free(e1->desc);
    e1->desc = e2->desc;
}


void entryInsert(sl_t *sl){
    char *word = getWord();
    char *desc = read_line();
    entry_t *e = createEntry(word, desc);
    if (slInsert(sl, e) == 0) errorMessage(1);
}

void entryChange(sl_t *sl){
    char *word = getWord();
    char *desc = read_line();

    entry_t *find = createEntry(word, NULL);

    if (find == NULL) 
        errorMessage(1);
    else
    {
        entry_t *e = createEntry(word, desc);
        slChange(sl, e);
    }
    free(word);
}

void entryRemove(sl_t *sl){
    char *word = getWord();
    entry_t *e = createEntry(word, NULL);
    if (slRemove(sl, e) == 0) errorMessage(1);
    free(word);
}

void entrySearch(sl_t *sl){
    char *word = getWord();
    entry_t *find = createEntry(word, NULL);
    entry_t *e = slSearch(sl, find);

    if (e == NULL) 
        errorMessage(1);
    else
    {
        entryPrint(e);
        free(find);
    }
    free(word);
}

void entryPrintAll(sl_t *sl){
    char c = getchar();
    entry_t *e = createEntry(&c, NULL);

    if (slPrintWordsStartedWith(sl, e) == 0)
        printf("NAO HA PALAVRAS INICIADAS POR %c", c);
}

void entryPrint(entry_t *e){
    printf("%s %s\n", e->word, e->desc);
}


int operationDecider(sl_t *sl){
    char *op = getWord();
    if (strcmp(op, "insercao") == 0)
        entryInsert(sl);
    else if (strcmp(op, "remocao") == 0)
        entryRemove(sl);
    else if (strcmp(op, "alteracao") == 0)
        entryChange(sl);
    else if (strcmp(op, "busca") == 0)
        entrySearch(sl);
    else 
        entryPrintAll(sl);
    
    char c = getchar();
    if (c == EOF) return 0;
    else 
    {
        ungetc(c, stdin);
        return 1;
    }
    free(op);
}

void errorMessage(int i){
    if (i == 1)
        printf("OPERACAO INVALIDA\n");
    else
        printf("NAO HA PALAVARAS INICIADAS");
}