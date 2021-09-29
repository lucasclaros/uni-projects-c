/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 27/09/2021 00:32
 *   Modified time: 29/09/2021 06:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

struct Input
{
    char *text;
    int maxWords;
};

struct Word
{
    char *word;
    int count;
};

struct Frequent_words
{
    int elements;
    word_t **vec_words;      
};


/** 
 *  Get char by char from stdin reallocating properly
 * until a \n is read(it ignores \r). At the end, a \0 is setted to
 * close the string. If EOF is reached, it changes the variable isEOF
 */
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

input_t *inputCreate(){
    input_t *t = malloc(sizeof(input_t));
    if (t == NULL)
        return NULL;

    t->text = NULL;
    return t;
}

int inputDestroy(input_t *t){
    if(t == NULL)
        return -1;

    free(t->text);
    free(t);
    return 1;
}

bool inputRead(input_t *t){
    bool isEOF = FALSE;

    t->text = read_line();
    scanf("%d", &t->maxWords); getchar();

    if ( getchar() == EOF)
        isEOF = TRUE;
    return isEOF;
}

/**
 *  This function creates a word_t* vector by looping 
 * through all words in the text given with strtok() and 
 * each word_t* stores a word and its frequency in text.
 * 
 * If a word_t* was already added, it just increases the counter by 1. 
 */
freq_words_t *wordCounter(input_t *t){
    freq_words_t *f = freqWordsCreate();
    if (f == NULL) return NULL;

    char *token = strtok(t->text, " ");
    while (token != NULL)
    {
        word_t **word = wasAddedtoVector(f, token);

        if (word == NULL)
            addWordtoVector(f, token);
        else
            (*word)->count++;

        token = strtok(NULL, " ");
    }
    
    insertionSortAlphabetical(f->vec_words, f->elements);
    insertionSort(f->vec_words, f->elements);
    return f;
}

int addWordtoVector(freq_words_t *f, char *src){
    if (f == NULL) return -1;

    word_t *word = malloc(sizeof(word_t));
    if (word == NULL) return -1;

    word->count = 1;
    word->word = malloc((strlen(src)+1)* sizeof(char));
    strcpy(word->word, src);

    f->vec_words = realloc(f->vec_words, (f->elements+1) * sizeof(word_t *));
    f->vec_words[f->elements++] = word;
    return 1;
}

word_t **wasAddedtoVector(freq_words_t *f, char *word){
    for (int i = 0; i < f->elements; i++)
        if (strcmp(f->vec_words[i]->word, word) == 0)
            return &f->vec_words[i];
    return NULL;
}

freq_words_t *freqWordsCreate(){
    freq_words_t *f = malloc(sizeof(freq_words_t));
    if (f == NULL) return NULL;

    f->elements = 0;
    f->vec_words = NULL;
    return f;
}

int freqWordsDestroy(freq_words_t *f){
    if (f == NULL) return -1;

    for (int i = 0; i < f->elements; i++)
    {
        free(f->vec_words[i]->word);
        free(f->vec_words[i]);
    }
    free(f->vec_words);
    free(f);
    return 1;
}

void freqWordsPrint(input_t *t, freq_words_t *f){
    int elementstoPrint;

    if (t->maxWords > f->elements) elementstoPrint = f->elements;
    else elementstoPrint = t->maxWords;

    for (int i = 0; i < elementstoPrint; i++)
        printf("%s %d\n", f->vec_words[i]->word, f->vec_words[i]->count);
}

void insertionSort(word_t **vec_words, int nElements)
{
    int i, key, j;
    for (i = 1; i < nElements; i++) {
        word_t *prev_address = vec_words[i];
        key = vec_words[i]->count;
        j = i - 1;

        while (j >= 0 && vec_words[j]->count < key) {
            vec_words[j + 1] = vec_words[j];
            j = j - 1;
        }

        vec_words[j + 1] = prev_address;
    }
}

void insertionSortAlphabetical(word_t **vec_words, int nElements)
{
    int i, j;
    char *key;
    for (i = 1; i < nElements; i++) {
        word_t *prev_address = vec_words[i];
        key = vec_words[i]->word;
        j = i - 1;

        while (j >= 0 && strcmp(vec_words[j]->word, key) > 0) {
            vec_words[j + 1] = vec_words[j];
            j = j - 1;
        }
        vec_words[j + 1] = prev_address;
    }
}
