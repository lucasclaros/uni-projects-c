#include <stdio.h>

int main() {
    double entrada[4],min,res,soma;
    //le entradas
    for (int i = 0; i < 4; i++)
    {
        scanf("%lf", &entrada[i]);
    }
    min=entrada[0]; //fixa um valor para comparacao
    //i percorre o vetor
    for (int i = 0; i < 4; i++)
    {
        //se existir um valor menor que o ultimo lido, min assume esse valor
        if (min >= entrada[i])
        {
            min = entrada[i];
        }
        //soma das entradas
        soma += entrada[i];
    }

    res = (soma-min)/3;
    printf("%.4f", res);
    
    return 0;
}