#include <stdio.h>

float multa, vel, limite = 80;


int main() {
    scanf("%f", &vel);
    
    if(vel <= limite){
        printf("Velocidade dentro do limite permitido. \n");
    }else{
        multa = 2 * (vel - limite);
        printf("Limite de velocidade excedido! Multado no valor de R$%.2f! \n", multa);
    }
    
    return 0;
}