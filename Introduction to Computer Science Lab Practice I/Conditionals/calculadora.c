#include <stdio.h>

float a, b;
char op;

int main() {
    scanf("%f %c %f", &a, &op, &b);
    
    switch(op){
        case '+':
            printf("%.6f", a + b);
            break;
        case '-':
            printf("%.6f", a - b);
            break;
        case '*':
            printf("%.6f", a * b);
            break;
        case '/':
            printf("%.6f", a / b);
            break;
        case '%':
            printf("%.6f", (a / b) * 100);
            break;
    }
    
    return 0;
}