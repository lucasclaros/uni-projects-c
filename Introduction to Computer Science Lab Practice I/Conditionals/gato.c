#include <stdio.h>

int brincou, mordeu, calorias;

int main() {
    scanf("%d %d", &brincou, &mordeu);
    calorias = 5*brincou - 3*mordeu;
    
    if(calorias >= 30){
        printf("P");
    }else if(calorias >= 0 && calorias < 30){
        printf("B");
    }else{
        printf("R");
    }
    
    return 0;
}