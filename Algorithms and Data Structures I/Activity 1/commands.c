#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"

struct Input
{
    char *text;
    int nWords;
};

struct Word
{
    char *word;
    int count;
};

struct Freq_words
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

freq_words_t *freqWordCreate(){
    freq_words_t *f = malloc(sizeof(freq_words_t));
    if (f == NULL)
        return NULL;

    f->elements = 0;
    f->vec_words = NULL;
    return f;
}
int freqWordDestroy(freq_words_t *f){
    if(f == NULL)
        return -1;

    for (int i = 0; i < f->elements; i++)
    {
        free(f->vec_words[i]->word);
        free(f->vec_words[i]);
    }
    free(f->vec_words);
    free(f);
    return 1;
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

int inputPrint(input_t *t){
    if(t == NULL)
        return -1;

    printf("%s\n%d\n", t->text, t->nWords);
    return 1;
}

bool inputRead(input_t *t){
    bool isEOF = FALSE;
    t->text = read_line();
    scanf("%d", &t->nWords); getchar();
    if ( getchar() == EOF)
        isEOF = TRUE;
    return isEOF;
}

word_t **wordCheck(freq_words_t *f, char *word){
    for (int i = 0; i < f->elements; i++)
        if (strcmp(f->vec_words[i]->word, word) == 0)
            return &f->vec_words[i];
    return NULL;
}

void freqWordPrint(input_t *t, freq_words_t *f){
    int i, index;
    if (t->nWords > f->elements) index = f->elements;
    else index = t->nWords;
    for (i = 0; i < index; i++)
        printf("%s %d\n", f->vec_words[i]->word, f->vec_words[i]->count);
}

void insertionSort(freq_words_t *f, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        word_t *p_address = f->vec_words[i];
        key = f->vec_words[i]->count;
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && f->vec_words[j]->count < key) {
            f->vec_words[j + 1] = f->vec_words[j];
            j = j - 1;
        }

        while (j >= 0 && strcmp(f->vec_words[j]->word, f->vec_words[j]->word) > 0) {
            f->vec_words[j + 1] = f->vec_words[j];
            j = j - 1;
        }
        f->vec_words[j + 1] = p_address;
    }
}

void insertionSortAlphabetical(freq_words_t *f, int n)
{
    int i, j;
    char *key;
    for (i = 1; i < n; i++) {
        word_t *p_address = f->vec_words[i];
        key = f->vec_words[i]->word;
        j = i - 1;

        while (j >= 0 && strcmp(f->vec_words[j]->word, key) > 0) {
            f->vec_words[j + 1] = f->vec_words[j];
            j = j - 1;
        }
        f->vec_words[j + 1] = p_address;
    }
}

freq_words_t *wordCount(input_t *t){
    freq_words_t *f = freqWordCreate();
    char *copy = malloc((strlen(t->text)+1) * sizeof(char));
    strcpy(copy, t->text);
    char *token = strtok(copy, " ");
    while (token != NULL)
    {
        word_t **w = wordCheck(f, token);
        if (w != NULL)
            w[0]->count++;
        else
        {
            word_t *w = malloc(sizeof(word_t));
            w->count = 1;
            w->word = malloc((strlen(token)+1)* sizeof(char));
            strcpy(w->word, token);
            f->vec_words = realloc(f->vec_words, (f->elements +1 ) * sizeof(word_t *));
            f->vec_words[f->elements++] = w;
        }
        token = strtok(NULL, " ");
    }
    free(copy);
    insertionSortAlphabetical(f, f->elements);
    insertionSort(f, f->elements);
    return f;
}