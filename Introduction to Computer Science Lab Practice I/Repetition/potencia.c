#include <stdio.h>

int main() {
    int base, expoente, aux=1;
    scanf("%d %d", &base, &expoente);
    for(int i = 0; i < expoente; i++){
        aux = base*aux;
    }
    printf("%d", aux);

}