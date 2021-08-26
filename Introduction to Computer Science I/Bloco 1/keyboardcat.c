#include <stdio.h>
int a, d, j, i;
char c[50];

int main() {

    //atribuindo os valores do teclado
    for(j = 0; j < 49; j++){
        scanf(" %c", &c[j]);    
    }

	//pegando a quantidade de caracteres e criando o vetor b
    scanf("%d", &a);
    int b[a];
    
    //passando a mensagem codificada para o vetor b
    for(j = 0; j < a; j++){
        scanf(" %d", &b[j]);
    }

	//pegando os numeros contidos em cada casa do vetor b e aplicando no vetor c para decodificar a mensagem
    for(i = 0; i < a; i++){
    	if(c[b[i]] == '_'){
    		printf(" ");
		}else if(c[b[i]] == 'E'){
			printf("\n");
		}else{
			printf("%c", c[b[i]]);
		}
    }
    return 0;
}