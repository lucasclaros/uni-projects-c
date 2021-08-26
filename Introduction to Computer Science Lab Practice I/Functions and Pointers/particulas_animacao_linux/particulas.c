#include <stdio.h>
#include <stdlib.h>
#include <time.h>
     
//constantes
#define LINHA 32
#define COLUNA 64
#define AREIA '#'
#define AGUA '~'
#define CIMENTO '@'
#define AR ' '
#define WAIT 150
#define clrscr() printf("\033[H\033[J")

//funcoes
void atualizaFisica();
void imprimeMatriz();
char mat_frames[LINHA][COLUNA];
void msleep(long msec){
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}

//comeco
int main () {
    int qtd_frames, frame_lido, frame_atual=0, x, y;
    char particula;

    //preenche de ar
    for (int i = 0; i < LINHA; i++)
        for (int j = 0; j < COLUNA; j++)
            mat_frames[i][j] = AR;

    scanf("%d", &qtd_frames);

    while(frame_atual < qtd_frames)
    {
        //checa se ainda tem entradas
        int a = scanf(" %d: %d %d %c", &frame_lido, &x, &y, &particula);
        //se for a ultima entrada, continua para o ultimo frame 
        if (a == EOF)
            frame_lido = qtd_frames;
        
        //atualiza o frame até o frame lido
        while (frame_atual < frame_lido)
        {
            clrscr();
            printf("frame: %d\n", frame_atual+1);
            imprimeMatriz();
            atualizaFisica();
            frame_atual++;
            msleep(WAIT);
        }
        //cria particula
        if (a != EOF)
            mat_frames[y][x] = particula;
    }
    return 0;
}


void atualizaFisica(){
    //faz a copia da matriz original
    char mat_copia[LINHA][COLUNA];
    for (int i = 0; i < LINHA; i++)
        for (int j = 0; j < COLUNA; j++)
            mat_copia[i][j] = mat_frames[i][j];

    //percorre toda a matriz
    for (int i = 0; i < LINHA; i++)
    { 
        for (int j = 0; j < COLUNA; j++)
        {
            //compara o estado atual da matriz e faz as mudanças na matriz copia
            switch (mat_frames[i][j])
            {
                case AR:
                case CIMENTO:
                default:   
                    break;
                case AREIA:
                    //checa se está dentro da matriz e o bloco imediatamente abaixo
                    if ((i+1 < LINHA) && (mat_frames[i+1][j] == AGUA || mat_frames[i+1][j] == AR))
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i+1][j];
                        mat_copia[i+1][j] = tmp;
                    }//checa se está dentro da matriz e o bloco a esquerda e abaixo
                    else if ((i+1 < LINHA && j-1 >= 0) && (mat_frames[i+1][j-1] == AGUA || mat_frames[i+1][j-1] == AR))
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i+1][j-1];
                        mat_copia[i+1][j-1] = tmp;
                    }
                    //checa se está dentro da matriz e o bloco a direita e abaixo
                    else if ((i+1 < LINHA && j+1 < COLUNA) && (mat_frames[i+1][j+1] == AGUA || mat_frames[i+1][j+1] == AR))
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i+1][j+1];
                        mat_copia[i+1][j+1] = tmp;
                    }    
                    break;
                case AGUA:
                    if (i+1 < LINHA && mat_frames[i+1][j] == AR)
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i+1][j];
                        mat_copia[i+1][j] = tmp;
                    }else if ((i+1 < LINHA && j-1 >= 0) && mat_frames[i+1][j-1] == AR)
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i+1][j-1];
                        mat_copia[i+1][j-1] = tmp;
                    }else if ((i+1 < LINHA && j+1 < COLUNA) && mat_frames[i+1][j+1] == AR)
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i+1][j+1];
                        mat_copia[i+1][j+1] = tmp;
                    }else if ((j-1 >= 0) && mat_frames[i][j-1] == AR)
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i][j-1];
                        mat_copia[i][j-1] = tmp;
                    }else if ((j+1 < COLUNA) && mat_frames[i][j+1] == AR)
                    {
                        char tmp = mat_copia[i][j];
                        mat_copia[i][j] = mat_copia[i][j+1];
                        mat_copia[i][j+1] = tmp;
                    }
                    break;
            }
        }
    }
    //por fim, joga a matriz copia com as modificacoes na
    //matriz original 
    for (int i = 0; i < LINHA; i++)
        for (int j = 0; j < COLUNA; j++)
            mat_frames[i][j] = mat_copia[i][j];
}


void imprimeMatriz(){
    for (int i = 0; i < LINHA; i++)
    {
        for (int j = 0; j < COLUNA; j++)
            printf("%c", mat_frames[i][j]);
        printf("\n");      
    }
}
