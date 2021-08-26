#include <stdio.h>
#include <math.h>

float a, b, r;

int main() {
    
    scanf("%f", &a);
    scanf("%f", &b);
    r = pow(a, b);
    printf("%.4f \n", r);
    
    return 0;
}