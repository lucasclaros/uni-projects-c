#include <stdio.h>
#include <stdlib.h>

char *read_line(char *);

int main(){

    int num_linhas, qtd_indices;
    //lê quantidade de linhas corrompidas e remove o buffer
    scanf("%d", &num_linhas);
    getchar();

    //matriz usada para salvar cada linha lida
    char **mensagem = calloc(num_linhas, sizeof(char *));
    for (int i = 0; i < num_linhas; i++)
        mensagem[i] = calloc(1, sizeof(char));

    //lê linha por linha, atribuindo na linha correspondente da matriz
    for (int i = 0; i < num_linhas; i++)
        mensagem[i] = read_line(mensagem[i]);

    scanf("%d", &qtd_indices);
    getchar();

    //lê os indices válidos, atribui no vetor indices e printa a frase correspondente do indice
    int indices[qtd_indices];
    for (int i = 0; i < qtd_indices; i++)
    {
        scanf("%d", &indices[i]);
        printf("%s\n", mensagem[indices[i]]);
    }

    for (int i =0; i < num_linhas; i++)
		free(mensagem[i]);
    free(mensagem);
    return 0;
}

char *read_line(char *linha){
    int c,k=0;
    while((c=getchar()) != '\n') // enquanto a leitura não chegar ao '\n'
    {
        // realoca mais um espaco na linha da matriz 
        // (k começa em 0 e a variavel já inicia com 1 de espaço, logo k+2 sempre irá adicionar um espaco a mais)
        linha = realloc(linha, (k+2) * sizeof(char));

        // adiciona o caractere lido na linha da matriz
        linha[k++] = c;
    }
    // \0 para completar a string quando chegar ao \n
    linha[k] = '\0';
    return linha;
}