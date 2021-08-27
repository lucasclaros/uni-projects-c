#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *read_line (char *);
void checaTabu (char *, char *, int *);

int main(){
    char *tabu = NULL, *frase = NULL;
    int qtd_vezes=0;
    tabu = read_line(tabu);
    frase = read_line(frase);
    checaTabu(tabu, frase, &qtd_vezes);
    printf("A palavra tabu foi encontrada %d vezes\n", qtd_vezes);
    printf("Frase: %s\n", frase);
    free(tabu);
    free(frase);
    return 0;
}

void checaTabu(char *tabu, char *frase, int *qtd_vezes){
    char *prox_tabu = strstr(frase, tabu);
    while (prox_tabu != NULL)
    {
        (*qtd_vezes)++;
        memmove(prox_tabu, prox_tabu+strlen(tabu), strlen(prox_tabu));
        prox_tabu = strstr(frase, tabu);
    }
}


char *read_line(char *linha){
    int c,k=0;
    linha = calloc(1, sizeof(char));
    while((c=getchar()) != '\n' && c != 36)
    {
        linha = realloc(linha, (k+2) * sizeof(char));
        linha[k++] = c;
    }
    linha[k] = '\0';
    return linha;
}