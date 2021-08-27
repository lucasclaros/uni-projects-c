#include <stdio.h>

int main() {
    int a[513], ponteiro=0,n1,n2,n3;
    char c;
    //lê todas as entradas
    for(int j = 0; j < 512; j++){
        scanf("%i", &a[j]);
    }
    printf("Saida do programa:\n");
    while(a[ponteiro] != 0){
        switch(a[ponteiro]){
            case 1:
                n1 = a[ponteiro+1];
                n2 = a[ponteiro+2];
                n3 = a[ponteiro+3];
                a[n3] = a[n1] + a[n2];
                ponteiro += 4; //proxima casa
                break;
            case 2:
                n1 = a[ponteiro+1];
                n2 = a[ponteiro+2];
                n3 = a[ponteiro+3];
                a[n3] = a[n1] * a[n2];
                ponteiro += 4;
                break;
            case 3:
                n1 = a[ponteiro+1];
                n2 = a[ponteiro+2];
                n3 = a[ponteiro+3];
                if(a[n1] < a[n2]){
                    a[n3] = 1;
                }else{
                    a[n3] = 0;
                }
                ponteiro += 4;
                break;
            case 4:
                n1 = a[ponteiro+1];
                n2 = a[ponteiro+2];
                n3 = a[ponteiro+3];
                if(a[n1] == a[n2]){
                    a[n3] = 1;
                }else{
                    a[n3] = 0;
                }
                ponteiro += 4;
                break;
            case 5:
                n1 = a[ponteiro+1];
                ponteiro = a[n1];
                break;
            case 6:
                n1 = a[ponteiro+1];
                n2 = a[ponteiro+2];
                if(a[n1] != 0){
                    ponteiro = a[n2];
                }else{
                    ponteiro += 3;
                }
                break;
            case 7:
                n1 = a[ponteiro+1];
                n2 = a[ponteiro+2];
                a[n2] = a[n1];
                ponteiro += 3;
                break;
            case 8:
                n1 = a[ponteiro+1];
                c = a[n1];
                printf("%c", c);
                ponteiro += 2;
                break;
            case 9:
                n1 = a[ponteiro+1];
                printf("%d", a[n1]);
                ponteiro += 2;
                break;
        }
    }
    
    printf("\nEstado final da fita:\n");
    for(int j = 0; j < 512; j++){
        printf("%i\n", a[j]);
    }
    
    return 0;
}