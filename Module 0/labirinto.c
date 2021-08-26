#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define VISITADO '*'
#define PESSOA '#'
#define CAMINHO '.'

typedef struct labirinto
{
    char *nome_arquivo;
    char **matriz;
    int linhas;
    int colunas;
    int pos_x;
    int pos_y;
    int pessoas;
    int paths_visitados;
    int paths_validos;
    double exploracao;
    bool is_EOF;
    bool the_end;
} Labirinto;

char *read_line();
char *read_line_arquivo(FILE *, Labirinto *);
void leArquivo(Labirinto *);
void percorreLabirinto(Labirinto *, int, int);
void imprimeResultado(Labirinto *);

int main(){
    Labirinto *labirinto;
    labirinto = calloc(1, sizeof(Labirinto));

    //le o nome do arquivo que contem o labirinto
    labirinto->nome_arquivo = NULL;
    labirinto->nome_arquivo = read_line(); 

    leArquivo(labirinto);
    percorreLabirinto(labirinto, labirinto->pos_x, labirinto->pos_y);
    imprimeResultado(labirinto);

    //desalocacao de memoria
    for (int i = 0; i < labirinto->linhas; i++)
        free(labirinto->matriz[i]);
    free(labirinto->matriz);
    free(labirinto->nome_arquivo);
    free(labirinto);
    return 0;
}

void leArquivo(Labirinto *labirinto){
    FILE *arquivo = fopen(labirinto->nome_arquivo, "r");
    fscanf(arquivo, "%d %d", &labirinto->linhas, &labirinto->colunas);
    fscanf(arquivo, "%d %d ", &labirinto->pos_x, &labirinto->pos_y);
    for(int i=0; !labirinto->is_EOF; i++)
    {
        labirinto->matriz    = realloc(labirinto->matriz, (i+1)*sizeof(char *));
        labirinto->matriz[i] = NULL;
        labirinto->matriz[i] = read_line_arquivo(arquivo, labirinto);
    }
    fclose(arquivo);
}

/*
// 1 - checa-se as bordas (saida do labirinto) .
// 2 - substitui o caminho por visitado e incrementa os caminhos visitados.
// 3 - checa-se o caminho livre na ordem: cima, direita, baixo, esquerda.
//      se há caminho livre, a funcao é chamada de forma recursiva com as
//      coordenadas do caminho livre seguindo a ordem acima, percorrendo
//      todo o labirinto.
*/
void percorreLabirinto(Labirinto *labirinto, int pos_x, int pos_y){
    if (
        pos_x == 0 || pos_x == (labirinto->linhas-1) ||
        pos_y == 0 || pos_y == (labirinto->colunas-1)
        )
    {
        labirinto->the_end = true;
    }
    if (labirinto->matriz[pos_x][pos_y] == CAMINHO)
    {
        labirinto->matriz[pos_x][pos_y] = VISITADO;
        labirinto->paths_visitados++;
    }
    if (!labirinto->the_end && labirinto->matriz[pos_x-1][pos_y] == CAMINHO)
        percorreLabirinto(labirinto, pos_x-1, pos_y);
    if (!labirinto->the_end && labirinto->matriz[pos_x][pos_y+1] == CAMINHO)
        percorreLabirinto(labirinto, pos_x, pos_y+1);
    if (!labirinto->the_end && labirinto->matriz[pos_x+1][pos_y] == CAMINHO)
        percorreLabirinto(labirinto, pos_x+1, pos_y);
    if (!labirinto->the_end && labirinto->matriz[pos_x][pos_y-1] == CAMINHO)
        percorreLabirinto(labirinto, pos_x, pos_y-1);
}

void imprimeResultado(Labirinto *labirinto){
    for (int i = 0; i < labirinto->linhas; i++)
        printf("%s\n", labirinto->matriz[i]);
    labirinto->exploracao = labirinto->paths_visitados * 100 / labirinto->paths_validos;
    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", labirinto->pessoas);
    printf("----Numero total de caminhos validos:   %d\n", labirinto->paths_validos);
    printf("----Numero total de caminhos visitados: %d\n", labirinto->paths_visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", labirinto->exploracao);
}

char *read_line_arquivo(FILE *arquivo, Labirinto *labirinto){
    int c,k=0;
    char *linha = NULL;
    while((c=fgetc(arquivo)) != EOF && c != '\n')
    {
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
        if (c == PESSOA)
            labirinto->pessoas++;
        else if (c == CAMINHO)
            labirinto->paths_validos++;        
    }
    c == EOF ? labirinto->is_EOF = true : 0;
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != EOF && c != '\n')
    {
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}