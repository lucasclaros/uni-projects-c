#include <stdio.h>
int linhas, ultima_linha, b, qtd_caracteres = 1, qtd_espacos;
char c;

int main() {
   
    scanf("%i %c", &linhas, &c);
    if(linhas <= 25 && linhas > 0){
        
        ultima_linha = (1 + (linhas-1)*2); //quantidade de caracter ultima linha
        qtd_espacos = (ultima_linha-1)/2; //quantidade de caracter até a metade da ultima linha
	for(int i = 0; i < linhas; i++){
           for(int j = 0; j < qtd_espacos; j++){
               printf(" ");
           }
           for(int k = 1; k <= qtd_caracteres; k++){
                   printf("%c", c);
           }
           printf("\n");
           qtd_caracteres+=2; //quantidade de caracter por linha
           qtd_espacos--; //remove o espaco para novo caracter
        }
    }else{
        printf("Altura invalida");
    }
    return 0;
}