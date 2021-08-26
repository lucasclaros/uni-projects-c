#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RAIO_CRUZ_NEUMANN 2
#define RAIO_CRUZ_MOORE 1

typedef struct dados
{
    char **matriz;
    int total_linhas;
    int total_colunas;
    int geracoes;
    int linha_atual;
    int coluna_atual;
    int viz_celViva;
    int viz_celMorta;
} Automato;

//funcoes
char *read_line(char *);
bool checaDados(int, int, int, char);
void criaAutomato(Automato *, char **, int, int, int);
void imprimeMatriz(Automato);
void copiaMatriz(Automato automato, char **matriz);
void modeloMoore(Automato);
void modeloNeumann(Automato);
void checaLinhasCruz(Automato, int *, char **, int);
void checaColunasCruz(Automato, int *, char **, int);
void checaDiagonaisCruz(Automato, int *, char **);

int main(){
    int linha, coluna, geracoes;   
    char modelo;
    scanf("%d %d\n %d\n %c", &linha, &coluna, &geracoes, &modelo);
    getchar();

    if (!checaDados(linha, coluna, geracoes, modelo))
        return 0; 

    char **mat_geracoes = calloc(linha, sizeof(char *));
    for (int i = 0; i < linha; i++)
        mat_geracoes[i] = read_line(mat_geracoes[i]);

    Automato automato;
    criaAutomato(&automato, mat_geracoes, geracoes, linha, coluna);

    if (modelo == 'M')
        modeloMoore(automato);
    else if (modelo == 'N')
        modeloNeumann(automato);

    imprimeMatriz(automato);

    //desalocacao
    for (int i = 0; i < linha; i++)
        free(mat_geracoes[i]);
    free(mat_geracoes);
    return 0;
}

bool checaDados(int linha, int coluna, int geracoes, char modelo){
    if (linha <= 0 || coluna <= 0 || geracoes <= 0 || (modelo != 'M' && modelo != 'N'))
    {
        printf("Dados de entrada apresentam erro.\n");
        return false;
    }else
        return true;
}

void criaAutomato(Automato *automato, char **mat_geracoes, int geracoes, int linha, int coluna){
    (*automato).matriz = mat_geracoes;
    (*automato).total_linhas = linha;
    (*automato).total_colunas= coluna;
    (*automato).geracoes = geracoes;
    (*automato).viz_celMorta = 0;
    (*automato).viz_celViva = 0;
}

void copiaMatriz(Automato automato, char **matriz){
    for (int i = 0; i < automato.total_linhas; i++)
        for (int j = 0; j < automato.total_colunas; j++)
            matriz[i][j] = automato.matriz[i][j];
}

void imprimeMatriz(Automato automato){
    for (int i = 0; i < automato.total_linhas; i++)
    {
        for (int j = 0; j < automato.total_colunas; j++)
            printf("%c", automato.matriz[i][j]);
        printf("\n");
    }
}

char *read_line(char *linha){
    int c,k=0;
    linha = calloc(1, sizeof(char));
    while((c=getchar()) != '\n')
    {
        linha = realloc(linha, (k+2) * sizeof(char));
        linha[k++] = c;
    }
    linha[k] = '\0';
    return linha;
}

/*
    A ideia é ir checando as células em formato de cruz e aumentando seu raio.

    No modelo de Neumann, como o raio máximo é 2, o for itera 2 vezes checando primeiro raio da cruz e assim por diante.
    No modelo de Moore, há uma cruz de raio 1 podendo ser reaproveitado o código de Neumann e as diagonais com uma lógica a parte.

*/


void modeloMoore(Automato automato){

    char **mat_copia = calloc(automato.total_linhas, sizeof(char*));
    for (int i = 0; i < automato.total_linhas; i++)
        mat_copia[i] = calloc((automato.total_colunas)+1, sizeof(char)); //+1 pelo \0 da string

    copiaMatriz(automato, mat_copia);

    for(int i = 0; i < automato.geracoes; i++)
    {
        for(int lin = 0; lin < automato.total_linhas; lin++)
        {
            automato.linha_atual = lin;
            for (int col = 0; col < automato.total_colunas; col++)
            {
                automato.viz_celMorta=0;
                automato.viz_celViva=0;
                automato.coluna_atual = col;
                switch (mat_copia[lin][col])
                {
                    case 'x':
                        checaLinhasCruz(automato, &automato.viz_celViva, mat_copia, RAIO_CRUZ_MOORE);
                        checaColunasCruz(automato, &automato.viz_celViva, mat_copia, RAIO_CRUZ_MOORE);
                        checaDiagonaisCruz(automato, &automato.viz_celViva, mat_copia);
                        break;
                    case '.':
                        checaLinhasCruz(automato, &automato.viz_celMorta, mat_copia, RAIO_CRUZ_MOORE);
                        checaColunasCruz(automato, &automato.viz_celMorta, mat_copia, RAIO_CRUZ_MOORE);
                        checaDiagonaisCruz(automato, &automato.viz_celMorta, mat_copia);
                        break; 
                    default:
                        break;
                }
                if (mat_copia[lin][col] == 'x' && (automato.viz_celViva < 2 || automato.viz_celViva > 3))
                    automato.matriz[lin][col] = '.';
                if (automato.viz_celMorta == 3)
                    automato.matriz[lin][col] = 'x';
            }
        }
        copiaMatriz(automato, mat_copia);
    }
    for (int i = 0; i < automato.total_linhas; i++)
        free(mat_copia[i]);
    free(mat_copia);
}

void modeloNeumann(Automato automato){

    char **mat_copia = calloc(automato.total_linhas, sizeof(char*));
    for (int i = 0; i < automato.total_linhas; i++)
        mat_copia[i] = calloc((automato.total_colunas)+1, sizeof(char)); //+1 pelo \0 da string
    
    copiaMatriz(automato, mat_copia);

    for(int i = 0; i < automato.geracoes; i++)
    {
        for(int lin = 0; lin < automato.total_linhas; lin++)
        {
            automato.linha_atual = lin;
            for (int col = 0; col < automato.total_colunas; col++)
            {
                automato.viz_celMorta=0;
                automato.viz_celViva=0;
                automato.coluna_atual = col;
                switch (mat_copia[lin][col])
                {
                    case 'x':
                        for (int raio = 1; raio <= RAIO_CRUZ_NEUMANN; raio++)
                        {
                            checaLinhasCruz(automato, &automato.viz_celViva, mat_copia, raio);
                            checaColunasCruz(automato, &automato.viz_celViva, mat_copia, raio);                          
                        }
                        break;

                    case '.':
                        for (int raio = 1; raio < 3; raio++)
                        {
                            checaLinhasCruz(automato, &automato.viz_celMorta, mat_copia, raio);
                            checaColunasCruz(automato, &automato.viz_celMorta, mat_copia, raio);                          
                        }
                        break;
                    default:
                        break;
                }
                if (mat_copia[lin][col] == 'x' && (automato.viz_celViva < 2 || automato.viz_celViva > 3))
                    automato.matriz[lin][col] = '.';
                if (automato.viz_celMorta == 3)
                    automato.matriz[lin][col] = 'x';
            }
        }
        copiaMatriz(automato, mat_copia);   
    }

    for (int i = 0; i < automato.total_linhas; i++)
        free(mat_copia[i]);
    free(mat_copia);
}

void checaLinhasCruz(Automato automato, int *vizinhos, char **mat_copia, int raio){
    int primeira_linha = 0, segunda_linha = 1, penultima_linha = automato.total_linhas-2, ultima_linha = automato.total_linhas-1;

    //checa o lado direito da celula (somando raio)
    if (automato.linha_atual == ultima_linha && automato.linha_atual+raio > ultima_linha)
    {
        if (mat_copia[raio-1][automato.coluna_atual] == 'x') 
            (*vizinhos)++;
    }else if (automato.linha_atual == penultima_linha && automato.linha_atual+raio > ultima_linha)
    {
        if (mat_copia[primeira_linha][automato.coluna_atual] == 'x')
            (*vizinhos)++;
    }else
        if (mat_copia[automato.linha_atual+raio][automato.coluna_atual] == 'x')
            (*vizinhos)++;

    //checa o lado esquerdo da celula (subtraindo raio)
    if (automato.linha_atual == primeira_linha && automato.linha_atual-raio < 0)
    {
        if (mat_copia[automato.total_linhas-raio][automato.coluna_atual] == 'x')
            (*vizinhos)++;
    }else if (automato.linha_atual == segunda_linha && automato.linha_atual-raio < 0)
    {
        if (mat_copia[automato.total_linhas+1-raio][automato.coluna_atual] == 'x')
            (*vizinhos)++;
    }else
        if (mat_copia[automato.linha_atual-raio][automato.coluna_atual] == 'x')
            (*vizinhos)++;
}

void checaColunasCruz(Automato automato, int *vizinhos, char **mat_copia, int raio){
    int primeira_coluna = 0, segunda_coluna = 1, penultima_coluna = automato.total_colunas-2, ultima_coluna = automato.total_colunas-1;

    //checa a parte de baixo da celula (somando raio)
    if (automato.coluna_atual == ultima_coluna && automato.coluna_atual+raio > ultima_coluna)
    {
        if (mat_copia[automato.linha_atual][raio-1] == 'x')
            (*vizinhos)++;
    }else if (automato.coluna_atual == penultima_coluna && automato.coluna_atual+raio > ultima_coluna)
    {
        if (mat_copia[automato.linha_atual][primeira_coluna] == 'x')
            (*vizinhos)++;
    }else
        if (mat_copia[automato.linha_atual][automato.coluna_atual+raio] == 'x')
            (*vizinhos)++;
    
    //checa a parte de cima da celula (subtraindo raio)
    if (automato.coluna_atual == primeira_coluna && automato.coluna_atual-raio < 0)
    {
        if (mat_copia[automato.linha_atual][automato.total_colunas-raio] == 'x')
            (*vizinhos)++;
    }else if (automato.coluna_atual == segunda_coluna && automato.coluna_atual-raio < 0)
    {
        if (mat_copia[automato.linha_atual][ultima_coluna] == 'x')
            (*vizinhos)++;
    }else
        if (mat_copia[automato.linha_atual][automato.coluna_atual-raio] == 'x')
            (*vizinhos)++;
}

void checaDiagonaisCruz(Automato automato, int *vizinhos, char **mat_copia){
    int primeira_coluna = 0, primeira_linha = 0, ultima_linha = automato.total_linhas-1, ultima_coluna = automato.total_colunas-1;

    for (int raio = -1; raio <= RAIO_CRUZ_MOORE; raio++)
    {
        if (raio == 0) // skipa as casa que a já foram checadas na etapa da cruz
            continue;
        else 
        {
            if (automato.coluna_atual+raio > ultima_coluna)
            {
                if (automato.linha_atual == primeira_linha)
                {
                    if (mat_copia[ultima_linha][primeira_coluna] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[automato.linha_atual+1][primeira_coluna] == 'x')
                        (*vizinhos)++;
                }else if (automato.linha_atual == ultima_linha)
                {
                    if (mat_copia[automato.linha_atual-1][primeira_coluna] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[primeira_linha][primeira_coluna] == 'x')
                        (*vizinhos)++;
                }else
                {
                    if (mat_copia[automato.linha_atual-1][primeira_coluna] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[automato.linha_atual+1][primeira_coluna] == 'x')
                        (*vizinhos)++;
                }
            }else if (automato.coluna_atual+raio < 0)
            {
                if (automato.linha_atual == primeira_linha)
                {
                    if (mat_copia[ultima_linha][ultima_coluna] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[automato.linha_atual+1][ultima_coluna] == 'x')
                        (*vizinhos)++;
                }else if (automato.linha_atual == ultima_linha)
                {
                    if (mat_copia[automato.linha_atual-1][ultima_coluna] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[primeira_linha][ultima_coluna] == 'x')
                        (*vizinhos)++;
                }else
                {
                    if (mat_copia[automato.linha_atual-1][ultima_coluna] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[automato.linha_atual+1][ultima_coluna] == 'x')
                        (*vizinhos)++;
                }
            }else
            {
                if (automato.linha_atual == primeira_linha)
                {
                    if (mat_copia[ultima_linha][automato.coluna_atual+raio] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[automato.linha_atual+1][automato.coluna_atual+raio] == 'x')
                        (*vizinhos)++;
                }else if (automato.linha_atual == ultima_linha)
                {
                    if (mat_copia[automato.linha_atual-1][automato.coluna_atual+raio] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[primeira_linha][automato.coluna_atual+raio] == 'x')
                        (*vizinhos)++;
                }else
                {
                    if (mat_copia[automato.linha_atual-1][automato.coluna_atual+raio] == 'x')
                        (*vizinhos)++;
                    if (mat_copia[automato.linha_atual+1][automato.coluna_atual+raio] == 'x')
                        (*vizinhos)++;
                }
            }

        }
    }
}