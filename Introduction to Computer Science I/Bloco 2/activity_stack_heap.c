#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("\n\n\t **** Bem vindo ao programa que explica de forma dinamica a diferenca entre memoria Stack e Heap ****\t\n\n");
    printf(
    "\n\n\t\tA memoria Stack e' uma parte da memoria do computador normalmente alocada no comeco da execucao do programa\n"
    "\tresponsavel por guardar blocos de codigo do nosso programa sejam eles variaveis, funcoes, procedimentos, etc. de tamanhos\n"
    "\tconhecidos. E' uma parte mais organizada porem limitada e seu tamanho varia de acordo com cada SO, geralmente no Windows o\n"
    "\ttamanho e' 1MB e em sistemas Unix e' 8MB. Ja a memoria Heap e' todo o resto de memoria que esteja disponivel, sendo limitada\n"
    "\tpela capacidade maxima que o computador que esta rodando o programa possui. Na Stack os dados sao guardados sequencialmente\n"
    "\tcomo uma pilha (proprio nome ja diz stack -> pilha) enquanto na memoria Heap nem sempre eles sao sequenciais, a memoria fica \"jogada\"\n"
    "\tem uma especie de amontoado de enderecos (heap -> monte).\n\n\n"
    );

    int numero = 25, tweetSize; // aloca 4 bytes na memoria stack para a variavel numero e tweetSize
    char letra = 'a'; // aloca 1 byte na memoria stack para a variavel letra
    char tweet[280]; // aloca 280 bytes na memoria stack para a variavel numero
    int *numero2 = malloc(3 * sizeof(int)); // aloca 3*(4 bytes) na memoria heap, o ponteiro numero2 aponta para o endereco correspondente
    char *letra2 = malloc(sizeof(char)); // aloca 1 byte na memoria heap, o ponteiro letra2 aponta para o endereco correspondente
    char *tweet2 = malloc(280 * sizeof(char)); // aloca 280*(1 byte) na memoria heap, o ponteiro tweet2 aponta para o endereco correspondente
    *numero2 = 28;
    *letra2 = 't';
    
    printf("Escreva seu tweet(limite 280 caracteres): ");
    scanf("%[^\n]s", tweet);
    getchar();
    printf("Escreva seu tweet(sem limite (enter + (ctrl+z) + enter para encerrar)): ");
    for (tweetSize = 0; scanf("%c", &tweet2[tweetSize]) != EOF; tweetSize++)
        tweet2 = realloc(tweet2, (tweetSize+2) * sizeof(char)); // realoca mais um espaço enquanto for necessário
    getchar();
    printf("\n\n**** Sorria, voce esta na memoria Stack!! :) ****\n\n");
    printf("Tweet armazenado pela memoria Stack:\n%s\n\n", tweet);        
    printf("Informacoes gravadas como exemplo na memoria Stack: %d %c\n\n", numero, letra);
    printf("\n>>>>>> TRANSICAO PARA A MEMORIA HEAP >>>>>>\n\n");
    printf("\n**** Sorria, voce esta na memoria Heap!! :) ****\n\n");
    printf("Tweet armazenado pela memoria Heap:\n");
    for (int i = 0; i < tweetSize ; i++)
        printf("%c", tweet2[i]);

    printf("\nInformacoes gravadas como exemplo na memoria Heap: %d %c\n", *numero2, *letra2);


    printf(
    "\n\n\t\tA olho nu nao ha diferenca nenhuma nos dados ou algo relacionado, tudo parece bem e funcionando da mesma forma.\n"
    "\t\tPorem, se olharmos para onde esses dados estao sendo armazenados podemos ver a diferenca.\n\n\n"
    );

    printf("**** COMPARACAO DE ENDERECOS ****\n\n");
    printf("Enderecos Stack\n variavel numero: %p,\n variavel letra: %p,\n tweet: sequenciais(%p %p %p)\n\n", &numero, &letra, &tweet[0], &tweet[1], &tweet[2]);
    printf("Enderecos Heap\n variavel numero2: %p,\n variavel letra2: %p,\n tweet2: nem sempre sequenciais(%p %p %p)\n", numero2, letra2, &tweet2[0], &tweet2[1], &tweet2[2]);
    
    printf(
    "\n\n\t\tCom relacao a performance, a Stack pode ser mais rapida por ser organizada, de facil acesso e estatica porem como consequencia, seus espacos\n"
    "\tsao sempre fixos. Se voce declara uma string de 50 caracteres e usar somente 15, ela ainda ira continuar tendo 50 bytes de tamanho. Diferente da\n"
    "\tHeap, onde mesmo sendo comparativamente mais lenta por ser \"mais desorganizada\", ira alocar apenas o que realmente e' preciso para a string\n"
    "\tque nesse caso sao os 15 bytes de tamanho, sendo possivel aumentar fazendo uma realocacao. Logo, utilizamos a memoria Stack quando conhecemos\n"
    "\to tamanho das nossas variaveis e estruturas e usamos a Heap quando a entrada do usuario e' de tamanho desconhecido ou podem variar de tamanho.\n\n\n"
    );

    printf("**** COMPARACAO DE TAMANHOS ****\n\n");
    printf("Tamanho Tweet Stack: %d bytes\n\n", sizeof(tweet));
    printf("Tamanho Tweet Heap: %d bytes\n", tweetSize-1);

    printf(
    "\n\n\t\tContudo, apesar de termos essa total liberdade para trabalharmos com uma indeterminada quantidade de memoria, e' preciso\n"
    "\ttotal atencao para a desalocacao dessa memoria apos seu uso.\n\n\n"
    );

    printf("**** DESALOCACAO DA MEMORIA ****\n\n");
    printf("Valores antes da desalocacao:\n");
    printf(" numero2 - endereco: %p | valor: %d\n letra2  - endereco: %p | valor: %c \n", numero2, *numero2, letra2, *letra2);
    
    free(numero2);
    free(letra2);
    free(tweet2);

    printf("\nValores depois da desalocacao:\n");
    printf(" numero2 - endereco: %p | valor: %d\n letra2  - endereco: %p | valor: %d \n", numero2, *numero2, letra2, *letra2);

    printf("\nPressione qualquer tecla para sair");
    getchar();
    return 0;
}