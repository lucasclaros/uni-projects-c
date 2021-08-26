#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//variaveis
#define POSICOES 26
#define ROTORES 3
int contadorRotor1=0, contadorRotor2=0, contadorRotor3=0;

//funcoes
void avancaRotor(int[ROTORES][POSICOES], int);
void atualizaRotores(int[ROTORES][POSICOES]);
char retornaChar(char[26], int);
int decryptaLetra(int[ROTORES][POSICOES], char[POSICOES], char);


//inicio
int main ()
{
    char alfabeto[POSICOES] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int rotores[ROTORES][POSICOES];
    char *mensagem = malloc(sizeof(char));

    scanf("%*[^\n]%*c"); 
    for(int j = 0; j < ROTORES; j++)
        for (int i = 0; i < POSICOES; i++)
            scanf("%d", &rotores[j][i]);
    scanf(" %*[^\n]%*c"); 

    int tamanhoString=0;
    for (tamanhoString = 0; scanf("%c", &mensagem[tamanhoString]) != EOF ; tamanhoString++) // enquanto a leitura não chegar ao EOF
        mensagem = realloc(mensagem, (tamanhoString+2) * sizeof(char));

    for (int j = 0; j < tamanhoString; j++)
        decryptaLetra(rotores, alfabeto, mensagem[j]); 

    free(mensagem);
    return 0;
}


int decryptaLetra(int rotores[ROTORES][POSICOES], char alfabeto[POSICOES], char charLido){
    int numeroEncryptado, checaMaiusculo=0;
    char charDecryptado;
    
    if (islower(charLido) == 0)
        checaMaiusculo = 1;
    charLido = tolower(charLido);

    //percorre o vetor do alfabeto
    for (int i = 0; i < POSICOES; i++)
    {
        numeroEncryptado = 0;
        if (charLido == alfabeto[i])
        {
            //pega o indice(i) do char (a = 0, b = 1, c = 2, ...) e verifica o valor no rotor1
            //pega o valor lido no rotor1 e aplica no endereco do rotor2
            //pega o valor lido no rotor2 e aplica no endereco do rotor3
            numeroEncryptado = rotores[2][rotores[1][rotores[0][i]]];
            //com o numero final guardado, transforma ele em char de novo
            charDecryptado = alfabeto[numeroEncryptado];
            //se o char lido anteriormente foi maiusculo, volta para o maiusculo
            if (checaMaiusculo == 1)
            {
                charDecryptado = toupper(charDecryptado);
                checaMaiusculo = 0;
            }
            
            printf("%c", charDecryptado);
            atualizaRotores(rotores);
            return 0;
        }
    }
    //se o char lido não estiver no alfabeto (char especial ou espaco)
    //printa o char especial
    printf("%c", charLido);
    return 0;
}


void avancaRotor(int rotores2[ROTORES][POSICOES], int rotor)
{
    int primeiroValor = rotores2[rotor][0];

    for (int i = 0; i < POSICOES; i++)
    {
        //se for a ultima casa, assume o valor da primeira casa salvo anteriormente
        if (i == (POSICOES-1)) 
            rotores2[rotor][i] = primeiroValor;
        else
            rotores2[rotor][i] = rotores2[rotor][i+1]; //se nao, assume o valor da proxima casa
    }
}

void atualizaRotores(int rotores[ROTORES][POSICOES])
{
    //as variaveis de contagem iniciam em 0, logo quando seu valor for 25 elas estarão completando uma volta
    //enquanto nao for < 25, avanca o rotor1
    if (contadorRotor1 < 25)
    {
        avancaRotor(rotores, 0);
        contadorRotor1++;
    }else if (contadorRotor2 < 25)
    {
        avancaRotor(rotores, 0); 
        contadorRotor1 = 0;
        avancaRotor(rotores, 1);
        contadorRotor2++;
    }else if (contadorRotor3 < 25)
    {
        avancaRotor(rotores, 0);
        contadorRotor1 = 0; 
        avancaRotor(rotores, 1); 
        contadorRotor2 = 0;
        avancaRotor(rotores, 2);
        contadorRotor3++;
    }else{
        avancaRotor(rotores, 0);
        contadorRotor1 = 0; 
        avancaRotor(rotores, 1);
        contadorRotor2 = 0; 
        avancaRotor(rotores, 2);
        contadorRotor3 = 0;
    }
}