#include <stdio.h>
int a;

int main() {
    scanf("%d", &a);
    switch(a){
        case 0:
            printf("* Morumbi\n");
	    printf("|\n");
        case 1:
            printf("* Butanta\n");
            printf("|\n");
        case 2:
            printf("* Pinheiros\n");
            printf("|\n");
        case 3:
            printf("* Faria Lima\n");
            printf("|\n");
        case 4:
            printf("* Fradique Coutinho\n");
            printf("|\n");
        case 5:
            printf("* Oscar Freire\n");
            break;
        case 6:
            printf("* Paulista\n");
            printf("|\n");
        case 7:
            printf("* Higienopolis-Mackenzie\n");
            printf("|\n");
        case 8:
            printf("* Republica\n");
            printf("|\n");
        case 9:
            printf("* Luz\n");
            break;
    }
    
    return 0;
}