#include <stdio.h>
#include <stdlib.h>

int main(){
    
    char *mensagem = calloc(1,sizeof(char));
    int qtd_char=0, qtd_palavras=0, qtd_linhas=0;

    for(qtd_char=0; scanf("%c", &mensagem[qtd_char]) != EOF; qtd_char++) // enquanto a leitura não chegar ao EOF
    {
        // realoca mais um espaco na string 
        mensagem = realloc(mensagem, (qtd_char+2) * sizeof(char));
        //(qtd_char começa em 0 e a variavel já inicia com 1 de espaço, logo qtd_char+2 sempre irá adicionar um espaco a mais)
        if (mensagem[qtd_char] == '\n')
        { 
            qtd_linhas++;
        }
    }

    for (int i = 0; mensagem[i] != '\0'; i++)  
    {
        //se for qualquer outro caractere, incrementa palavra
        if (mensagem[i] != ' ' && mensagem[i] != '\n' && mensagem[i] != '\t' && mensagem[i] != '\r' && mensagem[i] != '\0')
        {
            qtd_palavras++;
            //enquanto ele for caractere, percorre a palavra
            while (mensagem[i] != ' ' && mensagem[i] != '\n' && mensagem[i] != '\t' && mensagem[i] != '\r' && mensagem[i] != '\0')
            {
                i++;
            }
        }
    }

    printf("Linhas\tPalav.\tCarac.\n");
    printf("%d\t%d\t%d", qtd_linhas, qtd_palavras, qtd_char);
    free(mensagem);
    return 0;
}