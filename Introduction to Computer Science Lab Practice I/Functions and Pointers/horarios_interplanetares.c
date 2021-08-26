#include <stdio.h>
#include <stdlib.h>
//qtd de segundos no dia terrestre
#define TERRA 86400
#define VENUS 20995200
#define MERCURIO 5068800
#define JUPITER 35760

//funcoes
void conversao(unsigned long long *,unsigned long long,unsigned long long *,unsigned long long *,unsigned long long *,unsigned long long *);
void checaPlaneta(char [10],unsigned long long *,unsigned long long *,unsigned long long *,unsigned long long *,unsigned long long *);

//começo
int main(){
    unsigned long long segundosInput=0, dias=0, horas=0, minutos=0, segundos=0;
    char planeta[10]={};

    //le os segundos e o nome do planeta
    scanf("%llu %s", &segundosInput, planeta);
    printf("%llu segundos no planeta %s equivalem a:\n", segundosInput, planeta);
    checaPlaneta(planeta, &segundosInput, &dias, &horas, &minutos, &segundos);
    printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n", dias, horas, minutos, segundos);
    return 0;
}

void checaPlaneta(char planeta[10],unsigned long long *segundosInput,unsigned long long *dias,unsigned long long *horas,unsigned long long *minutos,unsigned long long *segundos){
    //verifica qual o planeta do input
    switch (planeta[0])
    {
    case 'T':
        conversao(segundosInput, TERRA, dias, horas, minutos, segundos);
        break;
    case 'V':
        conversao(segundosInput, VENUS, dias, horas, minutos, segundos);
        break;
    case 'M':
        conversao(segundosInput, MERCURIO, dias, horas, minutos, segundos);
        break;
    case 'J':
        conversao(segundosInput, JUPITER, dias, horas, minutos, segundos);
        break;
    default:
        break;
    }
}

void conversao(unsigned long long *segundosInput,unsigned long long segundos_planeta,unsigned long long *dias,unsigned long long *horas,unsigned long long *minutos,unsigned long long *segundos){

    for (int i = 0; *segundosInput > segundos_planeta; i++)
    {
        (*dias)++;
        *segundosInput-=segundos_planeta;
    }
    for (int i = 0; *segundosInput > 3600; i++)
    {
        (*horas)++;
        *segundosInput-=3600;
    }
    for (int i = 0; *segundosInput > 60; i++)
    {
        (*minutos)++;
        *segundosInput-=60;
    }
    *segundos = *segundosInput;
}