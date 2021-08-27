#include <stdio.h>


int main() {
    int dia;
    scanf("%d", &dia);
    printf("         Abril 2021         \n");
    printf(" Do  Se  Te  Qu  Qu  Se  Sa \n");
    
    //i comeca em -3 pois o mes só começa 4 dias depois do primeiro dia 
    for(int i = -3; i < 31; i++){
        if(i == dia) 
            printf("(%2d)", i);
        else if(i <= 0) //enquanto i <= 0, é impresso 4 espaços ocupando o lugar
                printf("    ");
            else
                printf(" %2d ", i);
        if(i == 3 || i == 10 || i == 17 || i == 24)
            printf("\n");
    }

    return 0;
}