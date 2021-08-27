#include <stdio.h>
#include <stdlib.h>


int la, ca, lb, cb, seed;

int main() {
    
    scanf("%d %d", &la, &ca);
    scanf("%d %d", &lb, &cb);
    if(la < 0 || ca < 0 || lb < 0 || cb < 0) {
        printf("Valores invalidos para a multiplicacao.");
        return 0;  
    }
    if(ca != lb){
        printf("Valores invalidos para a multiplicacao.");
        return 0;
    }
    scanf("%d", &seed);
    srand(seed);
    int matrizA[la][ca], matrizB[lb][cb], matrizC[la][cb];
    
    for(int i = 0; i < la; i++){
        for(int j = 0; j < ca; j++){
            matrizA[i][j] = rand()%50 - 25;
        }   
    }
    
    for(int i = 0; i < lb; i++){
        for(int j = 0; j < cb; j++){
            matrizB[i][j] = rand()%50 - 25;
        }   
    }
    int a = 0;
    for(int i = 0; i < la; i++){
        for(int j = 0; j < cb; j++){
            for(int k = 0; k < ca; k++){
                a += matrizA[i][k] * matrizB[k][j];
            }
            matrizC[i][j] = a;
            a = 0;
        }
    }
    for(int i = 0; i < la; i++){
        printf("Linha %d: ", i);
        for(int j = 0; j < cb; j++){
            printf("%d ", matrizC[i][j]);
        }
        printf("\n");
    }
    return 0;
}