#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//constantes da matriz de palavras spam
#define QTD_PALAVRAS 12
#define TAM_MAX_PALAVRA 9

//funcoes
bool checaLinha(int, char[]);
bool checaSpam(int, char[], char[][TAM_MAX_PALAVRA]);


int main(){
    int tam_mensagem;
    char *mensagem = malloc(sizeof(char));
    char spam[QTD_PALAVRAS][TAM_MAX_PALAVRA] = {
                    "gratuito", "atencao", "urgente", 
                    "imediato", "zoombie", "oferta", 
                    "dinheiro", "renda", "fundo",
                    "limitado", "ajuda", "SOS" };

    for(tam_mensagem=0; scanf("%c", &mensagem[tam_mensagem]) != EOF; tam_mensagem++) // enquanto a leitura não chegar ao EOF
        mensagem = realloc(mensagem, (tam_mensagem+2) * sizeof(char));
    
    bool a = checaLinha(tam_mensagem, mensagem);
    bool b = checaSpam(tam_mensagem, mensagem, spam);
    if (a || b)
        printf("Spam");
    else
        printf("Inbox");
    free(mensagem);
    return 0;
}


bool checaLinha(int tam_mensagem, char mensagem[tam_mensagem]){
    bool is_spam = false;
    //i percorre toda a mensagem
    for (int i = 0; i < tam_mensagem; i++)
    {   
        int n_chars=0;
        if (mensagem[i] != '\n' && mensagem[i] != '\r')
        {
            //enquanto nao chegar no final da linha, conta a qtd de chars
            while (mensagem[i] != '\n' && mensagem[i] != '\r')
            {
                n_chars++;
                i++;
            }
        }
        //checa a condicao do problema
        if (n_chars > 76)
            is_spam = true;
    }
    return is_spam;
}

bool checaSpam(int tam_mensagem, char mensagem[tam_mensagem], char spam[QTD_PALAVRAS][TAM_MAX_PALAVRA]){
    
    bool word_completed, is_spam=false;
    int spam_detected=0, j=0;
    //i percorre toda a mensagem
    for (int i = 0; i < tam_mensagem && !is_spam; i++)
    {
        //lin percorre as primeiras letras de cada palavra da matriz de palavras spam 
        for (int lin = 0; lin < QTD_PALAVRAS; lin++)
        {
            //verifica se a primeira letra da palavra encontrada na mensagem
            //é igual a alguma primeira letra das palavaras na matriz spam
            if (mensagem[i] == spam[lin][0])
            {
                //se for, percorre a palavra daquela linha para verificar se está completa
                for (j = 0; spam[lin][j] != '\0'; j++)
                {
                    //caso não esteja completa
                    if(mensagem[i+j] != spam[lin][j])
                    {
                        word_completed = false;
                        break;
                    }else
                        word_completed=true;
                }
                if (word_completed)
                    spam_detected++;
            }
        }
        if (spam_detected >= 2)
        {
            is_spam = true;
            break;
        }
        //se a primeira letra não está contida nos spams, vai até a próxima palavra
        if (mensagem[i] != ' ' && mensagem[i] != '\n' && mensagem[i] != '\t' && mensagem[i] != '\r')
        {
            while (mensagem[i] != ' ' && mensagem[i] != '\n' && mensagem[i] != '\t' && mensagem[i] != '\r')
            {
                i++;
            }
        }
    }

    return is_spam;
}