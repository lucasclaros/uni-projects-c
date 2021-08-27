#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
bool is_EOF = false;

char *read_line (char *);
char *achaUltimoSobrenome(char *, char *);

int main(){
    int qtd_nomes;
    char **nomes = NULL, *ultimoSobrenome=NULL;
    for (qtd_nomes = 0; !is_EOF ; qtd_nomes++)
    {
        nomes = realloc(nomes, (qtd_nomes+1) * sizeof(char *));
        nomes[qtd_nomes] = read_line(nomes[qtd_nomes]);
    }

    for (int i=0; i+1 < qtd_nomes; i+=2)
    {
        ultimoSobrenome = achaUltimoSobrenome(nomes[i], ultimoSobrenome);
        nomes[i+1] = realloc(nomes[i+1], (strlen(nomes[i+1])+2) * sizeof(char)); //+2 por causa do espaço e \0
        strcat(nomes[i+1], " ");
        nomes[i+1] = realloc(nomes[i+1], (strlen(nomes[i+1])+strlen(ultimoSobrenome)+1) * sizeof(char));
        strcat(nomes[i+1], ultimoSobrenome);
    }

    for (int i=0; i < qtd_nomes; i++)
        printf("%s\n", nomes[i]);

    for (int i = 0; i < qtd_nomes; i++)
        free(nomes[i]);
    free(nomes);
    free(ultimoSobrenome);
    return 0;
}


char *achaUltimoSobrenome(char *nome, char *ultimoSobrenome){
    int tamanhoNome = strlen(nome);
    char copia_nome[tamanhoNome+1];
    strcpy(copia_nome, nome);
    char *sobrenomes;
    sobrenomes = strtok(copia_nome, " ");
    while (sobrenomes != NULL)
    {
        free(ultimoSobrenome);
        ultimoSobrenome = calloc((strlen(sobrenomes)+1), sizeof(char));
        strcpy(ultimoSobrenome, sobrenomes);
        sobrenomes = strtok(NULL, " ");
    }
    return ultimoSobrenome;
}

char *read_line(char *linha){
    int c,k=0;
    linha = calloc(1, sizeof(char));
    while((c=getchar()) != '\n' && c != 36)
    {
        linha = realloc(linha, (k+2) * sizeof(char));
        linha[k++] = c;
    }
    if (c == 36)
        is_EOF = true;
    linha[k] = '\0';
    return linha;
}