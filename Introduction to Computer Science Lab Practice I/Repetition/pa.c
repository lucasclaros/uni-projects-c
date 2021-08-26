#include <stdio.h>

int a1, r, n;
long long an, soma;
int main() {
    scanf("%d", &a1);
    scanf("%d", &r);
    scanf("%d", &n);
    
    an = a1 + ((n-1)*r);
    soma = ((a1 + an)*n)/2;
    printf("%lld\n", an);
    printf("%lld\n", soma);

}