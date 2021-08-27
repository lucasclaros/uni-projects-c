#include <stdio.h>
#include <stdlib.h>
#include <math.h>


const int qtd_colunas = 3;

//funcoes
float dist_euclides(float coord2[][qtd_colunas], int pontos);
float dist_hermann(float coord2[][qtd_colunas], int pontos);
float calc_diagonal(float x1, float x2, float y1, float y2);
float calc_calcada(float x1, float x2, float y1, float y2);


int main() {
    int qtd_pontos=0, baldio=0, residencia=0, parque=0;;
    float diff=0;

    scanf("%d", &qtd_pontos);
    if(qtd_pontos <= 0){
        printf("Falha no processamento dos dados. \n");
        return 0;
    }

    //matriz com as coordenadas
    float coord[qtd_pontos][qtd_colunas];

    for (int i = 0; i < qtd_pontos; i++)
    {
        for (int j = 0; j < qtd_colunas; j++)
        {
            scanf("%f", &coord[i][j]);
        }

        //contagem de terrenos
        if(coord[i][2] == 0){
            residencia++;
        }else if(coord[i][2] == 1){
            parque++;
        }else if(coord[i][2] == -1){
            baldio++;
        }else{
            printf("Falha no processamento dos dados. \n");
            return 0;
        }
    }
    
    diff = fabs( dist_hermann(coord, qtd_pontos) - dist_euclides(coord, qtd_pontos) );

    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", baldio, residencia, parque);
    printf("A diferenca total de distancia percorrida foi de %.2f metros.", diff);
    return 0;
}

float dist_euclides(float coord2[][qtd_colunas], int pontos){
    float distancia=0;

    //percorre todas as linhas da matriz com as coordenadas
    for (int i = 0; i < pontos; i++)
    {
        //se for o ultimo ponto, calcula o retorno para casa (coord2[0][0], coord2[0][1])
        // 0 residencia, 1 parque, -1 baldio
        if(i == pontos-1){
            if(coord2[i][2] == 0){
                distancia += calc_calcada(coord2[i][0],coord2[0][0],coord2[i][1],coord2[0][1]);
            }else if(coord2[i][2] == 1 || coord2[i][2] == -1){
                distancia += calc_diagonal(coord2[i][0],coord2[0][0],coord2[i][1],coord2[0][1]);
            }
        }else if(coord2[i][2] == 0){
            distancia += calc_calcada(coord2[i][0],coord2[i+1][0],coord2[i][1],coord2[i+1][1]);
        }else if(coord2[i][2] == 1 || coord2[i][2] == -1){
            distancia += calc_diagonal(coord2[i][0],coord2[i+1][0],coord2[i][1],coord2[i+1][1]);
        }
    }
    return distancia;
}

float dist_hermann(float coord2[][qtd_colunas], int pontos){
    float distancia = 0;

    //percorre todas as linhas da matriz com as coordenadas
    for (int i = 0; i < pontos; i++)
    {
        //se for o ultimo ponto, calcula o retorno para casa (coord2[0][0], coord2[0][1])
        // 0 residencia, 1 parque, -1 baldio
        if(i == pontos-1){
            if(coord2[i][2] == 0 || coord2[i][2] == 1){
                distancia += calc_calcada(coord2[i][0],coord2[0][0],coord2[i][1],coord2[0][1]);
            }else if(coord2[i][2] == -1){
                distancia += calc_diagonal(coord2[i][0],coord2[0][0],coord2[i][1],coord2[0][1]);
            }
        }else if(coord2[i][2] == 0 || coord2[i][2] == 1){
            distancia += calc_calcada(coord2[i][0],coord2[i+1][0],coord2[i][1],coord2[i+1][1]);
        }else if( coord2[i][2] == -1){
            distancia += calc_diagonal(coord2[i][0],coord2[i+1][0],coord2[i][1],coord2[i+1][1]);
        }
    }
    return distancia;
}

float calc_diagonal(float x1, float x2, float y1, float y2){
    float resultado, deltaX, deltaY;
    deltaX = fabs(x2-x1);
    deltaY = fabs(y2-y1);
    resultado = sqrt( pow(deltaX,2) + pow(deltaY,2) ); //formula da distancia entre pontos
    return resultado;
}

float calc_calcada(float x1, float x2, float y1, float y2){
    float resultado, deltaX, deltaY;
    deltaX = fabs(x2-x1);
    deltaY = fabs(y2-y1);
    resultado = deltaX + deltaY;
    return resultado;
};
