#include <stdio.h>
#include <stdbool.h>

//variaveis
int pontosX=0, pontosO=0, casa=0;

//funcoes
int checaLinha(char [][3]);
int checaColuna(char [][3]);
int checaDiagonal(char [][3]);

//comeco
int main () {
    char jogo[3][3]={};
    //le as entradas 
    for(int i = 0; i < 3 ; i++) 
        for(int j = 0; j < 3; j++)
            scanf(" %c", &jogo[i][j]);
    
    //comeca a checar
    checaDiagonal(jogo);
    return 0;
}


int checaDiagonal(char jogo[3][3]){
    if (jogo[0][0] == jogo[1][1] && jogo[1][1] == jogo[2][2]) // verifica a diagonal principal
    {
        if (jogo[1][1] == 'x')
            printf("x ganhou");
        else if (jogo[1][1] == '0')
            printf("o ganhou");
    }else if (jogo[0][2] == jogo[1][1] && jogo[1][1] == jogo[2][0]) // verifica a diagonal secundária
    {
        if (jogo[1][1] == 'x')
            printf("x ganhou");
        else if (jogo[1][1] == 'o')
            printf("o ganhou");
    }else
        //se nada der certo, proxima checagem
        checaColuna(jogo);
    return 0;
}

int checaColuna(char jogo[3][3]){
    bool is_over = false;
    char ultCasa;
    //i percorre as linhas da matriz
    for(int i = 0; i < 3 ; i++) 
    {
        //a cada linha zera as variaveis de contagem de pontos e pega o valor da primeira casa da linha para comparacao
        pontosX=0;
        pontosO=0;
        ultCasa=jogo[0][i];
        //j percorre as colunas da matriz
        for(int j = 0; j < 3; j++)
        {
            //salva a informacao se há casas faltando (caso nenhuma checagem funcione, é verificado se faltam casas)
            if (jogo[i][j] == '-') 
                casa++;
            //compara se a casa atual é igual a ultima casa, se sim aumenta a variavel de contagem de pontos do respectivo jogador
            if(jogo[j][i] == ultCasa && ultCasa == 'x')
                pontosX++;
            else if(jogo[j][i] == ultCasa && ultCasa == 'o')
                pontosO++;

            //se houve 3 pontos iguais, o jogo acaba
            if(pontosX == 3)
            {
                printf("x ganhou");
                is_over = true;
            }else if(pontosO == 3)
            {
                printf("o ganhou");
                is_over = true;
            }
        }
    }
    //caso nada esteja correto, vai para ultima checagem
    if (!is_over)
        checaLinha(jogo);
    return 0;
}

int checaLinha(char jogo[3][3]){

    bool is_over = false;
    char ultCasa;
    //i percorre as linhas da matriz
    for(int i = 0; i < 3 ; i++) 
    {
        //a cada linha zera as variaveis de contagem de pontos e pega o valor da primeira casa para comparacao
        pontosX=0;
        pontosO=0;
        ultCasa=jogo[i][0];
        //j percorre as colunas da matriz
        for(int j = 0; j < 3; j++)
        {
            //salvar informacao se há casas faltando (caso nenhuma checagem funcione, é verificado se faltam casas)
            if (jogo[i][j] == '-')
                casa++;
            //compara se a casa atual é igual a ultima casa, se sim aumenta a variavel de contagem de pontos do respectivo jogador  
            if(jogo[i][j] == ultCasa && ultCasa == 'x')
                pontosX++;
            else if(jogo[i][j] == ultCasa && ultCasa == 'o')
                pontosO++;
            
            //se houve 3 pontos iguais, o jogo acaba
            if(pontosX == 3)
            {
                printf("x ganhou");
                is_over = true;
            }else if(pontosO == 3)
            {
                printf("o ganhou");
                is_over = true;
            }
        }
    }

    if (!is_over){
        if(casa > 0)
            printf("em jogo");
        else
            printf("empate");
    }
    return 0;
}