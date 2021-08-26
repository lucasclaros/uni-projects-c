#include <stdio.h>

int a, b;


int main() {

    scanf("%i", &a); //10  == 00001010
    scanf("%i", &b); //15  == 00001111
    
    printf("%i \n", a & b);  // 00001010  - 10
    printf("%i \n", a | b); // 00001111  - 15
    printf("%i \n", a ^ b);// 00000101 - 5
    printf("%i \n", ~a);// 11110101 
    printf("%i \n", ~b);// 11110000
    printf("%i \n", a >> 2);// 00101000 - 40
    printf("%i \n", b << 2);// 00111100 - 60
    
    return 0;
}