#include <stdio.h>
#include <stdlib.h>

char *read_line();

int main(){
    char *teste = NULL;
    teste = read_line();
    printf("%s", teste);
    free(teste);
    return 0;
}


char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != EOF)
    {
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}