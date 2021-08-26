#include <stdio.h>

int a, b = 255, d;
char c, vet1[4];

int main() {
    scanf("%i", &a);
    for(int i = 0; i < 4; i++){
        d = a & b;
        c = d;
        vet1[i] = c;
        a = a >> 8;
    }
    for(int i = 0; i < 4; i++){
        printf("%c", vet1[3-i]);
    }
    return 0;
}