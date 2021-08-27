#include <stdio.h>
#define QTD_VALORES 10

int calc_maior(int[QTD_VALORES]), calc_menor(int[QTD_VALORES]), calc_moda(int[QTD_VALORES]);
float calc_media(int[QTD_VALORES]);


int main () {
    int entrada[QTD_VALORES]={};
    for (int i = 0; i < 10; i++)
        scanf("%d", &entrada[i]);
    printf("%d ", calc_maior(entrada));
    printf("%d ", calc_menor(entrada));
    printf("%.2f ", calc_media(entrada));
    printf("%d ", calc_moda(entrada));
   return 0;
}

int calc_maior(int entrada[QTD_VALORES]){
    int valor=entrada[0];
    for (int i = 0; i < 10; i++)
        if (valor <= entrada[i])
            valor = entrada[i];
    return valor;
}

int calc_menor(int entrada[QTD_VALORES]){
    int valor=entrada[0];
    for (int i = 0; i < 10; i++)
        if (valor >= entrada[i])
            valor = entrada[i];
    return valor;
}

float calc_media(int entrada[QTD_VALORES]){
    float media=0;
    for (int i = 0; i < 10; i++)
        media += entrada[i];
    return media/10;
}

int calc_moda(int entrada[QTD_VALORES]){
    int contador=0, moda=entrada[0], aux=0;
    for (int j = 0; j < 10; j++)
    {
        //variavel que armazena quantas vezes o numero se repetiu
        contador=0;
        for (int i=0; i < 10 ;i++)
        {
            if(entrada[j]==entrada[i]){
                contador++;
            }
        }
        if (aux < contador)
        {
            aux = contador;
            moda = entrada[j];
        }
    }
    return moda;
}