#include <stdio.h>

float c, f;

int main() {
    
    scanf("%f", &f);
    
    c = (f - 32) * 5/9;
    
    printf("%.2f", c);
    
    return 0;
}