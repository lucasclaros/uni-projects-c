#include <stdio.h>

void calculaTroco(int *,int *,int *,int *,int *,int *,int *);

int main(){
    int valor_compra=0, moeda1r=0, moeda50=0, moeda25=0, moeda10=0, moeda5=0, moeda1c=0;
    scanf("%d", &valor_compra); 
    calculaTroco(&valor_compra, &moeda1r, &moeda50, &moeda25, &moeda10, &moeda5, &moeda1c); 
    printf("O valor consiste em %d moedas de 1 real\n", moeda1r);
    printf("O valor consiste em %d moedas de 50 centavos\n", moeda50);
    printf("O valor consiste em %d moedas de 25 centavos\n", moeda25);
    printf("O valor consiste em %d moedas de 10 centavos\n", moeda10);
    printf("O valor consiste em %d moedas de 5 centavos\n", moeda5);
    printf("O valor consiste em %d moedas de 1 centavo\n", moeda1c);

    return 0;
}


void calculaTroco(int *valor_compra, int *moeda1r,int *moeda50,int *moeda25,int *moeda10,int *moeda5,int *moeda1c){
    
    for (int i = 0; *valor_compra >= 100; i++)
    {
        (*moeda1r)++;
        *valor_compra-=100;
    }
    for (int i = 0; *valor_compra >= 50; i++)
    {
        (*moeda50)++;
        *valor_compra-=50;
    }
    for (int i = 0; *valor_compra >= 25; i++)
    {
        (*moeda25)++;
        *valor_compra-=25;
    }
    for (int i = 0; *valor_compra >= 10; i++)
    {
        (*moeda10)++;
        *valor_compra-=10;
    }
    for (int i = 0; *valor_compra >= 5; i++)
    {
        (*moeda5)++;
        *valor_compra-=5;
    }
    *moeda1c = *valor_compra;
}