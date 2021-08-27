#include <stdio.h>
#include <stdlib.h>

char *read_line(char *);
void imprimeMatriz(int **, int, int);

int main(){
    int largura, altura, qtdBorda;
    scanf("%d\n %d", &largura, &altura);

    int **imagem_original = calloc(altura, sizeof(int *));
    for (int i=0; i < altura; i++)
    {
        imagem_original[i] = calloc(largura, sizeof(int));
        for (int j = 0; j < largura; j++)
            scanf(" %d", &imagem_original[i][j]);
    }
    scanf(" %d", &qtdBorda);
    int novaAltura = (2*qtdBorda)+altura;
    int novaLargura = (2*qtdBorda)+largura;
    
    int **imagem_padding = calloc(novaAltura, sizeof(int *));
    for (int i=0; i < novaAltura; i++)
        imagem_padding[i] = calloc(novaLargura, sizeof(int));

    //o meio da matriz sempre começará na coord[borda][borda]  
    //e andará altura+borda e lagura+borda pois está dentro da matriz
    for (int i=qtdBorda; i < (qtdBorda+altura); i++)
        for (int j=qtdBorda; j < (qtdBorda+largura); j++)
            imagem_padding[i][j] = imagem_original[i-qtdBorda][j-qtdBorda];

    imprimeMatriz(imagem_padding, novaAltura, novaLargura);
    printf("\n");
    imprimeMatriz(imagem_original, altura, largura);

    for (int i=0; i < altura; i++)
       free(imagem_original[i]);
    for (int i=0; i < novaAltura; i++)
       free(imagem_padding[i]);
    free(imagem_original);
    free(imagem_padding);
    return 0;
}

void imprimeMatriz(int **matriz, int altura, int largura){
    for (int i=0; i < altura; i++)
    {
        for (int j=0; j < largura; j++)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
}

char *read_line(char *linha){
    int c,k=0;
    while((c=getchar()) != '\n')
    {
        linha = realloc(linha, (k+2) * sizeof(char));
        linha[k++] = c;
    }
    linha[k] = '\0';
    return linha;
}