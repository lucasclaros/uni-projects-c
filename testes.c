#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef enum bool { FALSE, TRUE} bool;
char *readLine();
char *readLineFile(FILE *, bool *);

int main(){
    char *filename = readLine();
    FILE *f = fopen(filename, "r+");
    char *word = NULL;
    if (f == NULL)
    {
        printf("errrou! %s\n", strerror(errno));   
        return 1;
    }else
    {
        bool isEOF = FALSE;
        while (!isEOF)
        {
            word = readLineFile(f, &isEOF);
            printf("%s\n", word);
            free(word);
            word = NULL;
        }
    }
    free(filename);
    fclose(f);
    return 0;
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