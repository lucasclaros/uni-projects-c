#include "commands.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void readWords(char *filename, list_t *l){
    FILE *f = fopen(filename, "r+");
    if (f == NULL)
    {
        printf("Error! %s\n", strerror(errno));   
        return;
    }

    bool isEOF = FALSE;
    while (!isEOF)
        listSortInsert(l, readLineFile(f, &isEOF));

    fclose(f);
}

char *readLine(){
    int c,k=0;
    char *line = NULL;
    while((c=getchar()) != '\n')
    {
        if (c == '\r') continue;
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    return line;
}

char *readLineFile(FILE *f, bool *is_EOF){
    int c,k=0;
    char *line = NULL;
    while((c=fgetc(f)) != EOF && c != '\n')
    {
        if (c == '\r') continue;
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    c == EOF ? *is_EOF = TRUE : 0;
    return line;
}

int checkInsertPrio(char *w1, char *w2){
    if (w1[0] < w2[0])
        return 1;
    else
        return 0;
}
