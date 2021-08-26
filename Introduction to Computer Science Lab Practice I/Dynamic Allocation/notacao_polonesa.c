#include <stdio.h>
#include <stdlib.h>

typedef struct pilha
{
    double *pilha;
    int ponteiro;
} Pilha;

void fazOperacao(Pilha *, char);

int main(){
    char caractere;
    Pilha pilha;
    pilha.pilha = NULL;
    pilha.ponteiro = 0;
    while (scanf(" %c", &caractere) != EOF)
    {
        if(caractere < 48)
        {
            getchar();
            fazOperacao(&pilha, caractere);
        }else 
        {
            ungetc(caractere, stdin);
            pilha.pilha = realloc(pilha.pilha, (pilha.ponteiro+1)*sizeof(double));
            scanf(" %lf ", &pilha.pilha[pilha.ponteiro++]);
        }
    }
    printf("Resultado: %lf\n", pilha.pilha[pilha.ponteiro-1]);
    free(pilha.pilha);
    return 0;
}


void fazOperacao(Pilha *pilha, char operador){
    double resultado = 0;
    switch (operador)
    {
        case '+':
            resultado = pilha->pilha[pilha->ponteiro-2] + pilha->pilha[pilha->ponteiro-1];
            break;
        case '-':
            resultado = pilha->pilha[pilha->ponteiro-2] - pilha->pilha[pilha->ponteiro-1];
            break;
        case '*':
            resultado = pilha->pilha[pilha->ponteiro-2] * pilha->pilha[pilha->ponteiro-1];
            break;
        case '/':
            resultado = pilha->pilha[pilha->ponteiro-2] / pilha->pilha[pilha->ponteiro-1];
            break;
        default:
            break;
    }
    
    pilha->pilha = realloc(pilha->pilha, (pilha->ponteiro-1)*sizeof(double));
    pilha->ponteiro -= 1;
    pilha->pilha[pilha->ponteiro-1] = resultado;

}