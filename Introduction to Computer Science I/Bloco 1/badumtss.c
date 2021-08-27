#include <stdio.h>

int num;

int main() {
    scanf("%i", &num);
    if(!(num % 11) && !(num % 13) && !(num % 19)){
        printf("BaDumTssTss");
    }else if(!(num % 11) && (num % 13) && (num % 19)){
        printf("BaBa");
    }else if((num % 11) && !(num % 13) && (num % 19)){
        printf("BaDum");
    }else if((num % 11) && (num % 13) && !(num % 19)){
        printf("BaTss");
    }else if(!(num % 11) && !(num % 13) && (num % 19)){
        printf("BaDumDum");
    }else if((num % 11) && !(num % 13) && !(num % 19)){
        printf("DumDumTss");
    }else if(!(num % 11) && (num % 13) && !(num % 19)){
        printf("BaDumTss");
    }else{
        printf("%i", num);
    }
    
    return 0;
}