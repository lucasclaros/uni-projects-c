#include <stdio.h>

int main() {
    float a1, razao, an, soma, aux=1;
    int qtd_termos;
    scanf("%f", &a1);
    scanf("%f", &razao);
    scanf("%d", &qtd_termos);

    //an = a1 * razao^(qtd_termos-1)
    for(int i = 0; i < (qtd_termos-1); i++){
        aux = razao*aux;
    }
    an = a1 * aux;

    //soma = a1 * (razao^qtd_termos - 1)/(razao - 1)
    aux = 1;
    for(int i = 0; i < qtd_termos; i++){
        aux = razao*aux;
    }
    soma = (a1 * (aux - 1)) / (razao - 1);
    printf("%.2f\n", an);
    printf("%.2f\n", soma);

}