#include <stdio.h>
#include <stdbool.h>
//aparentemente o enunciado tava bugado e as entradas tem 32 linhas e 65 colunas
//e nao 64 linhas e 32 colunas como escrito lá
#define LINHAS 32
#define COLUNAS 65
bool is_over = false, is_blank = false, passed = false;

//funcoes
void imprimeEsteira(char [][COLUNAS]);
void checaEsteira (char [][COLUNAS], int* , int* , char*);

//inicio
int main(){

    char esteira[LINHAS][COLUNAS]={}, lastChar;
    int line_mat,col_mat;
    

    //i percorre as linhas para leitura, j percorre as colunas
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
        {
            scanf("%c", &esteira[i][j]);
            if (esteira[i][j] == '[')
            {
                //salva o ponto de inicio
                line_mat = i;
                col_mat = j;
            }  
        }    

    //salva o primeiro char imediatamente apos o char de inicio para comparacao
    lastChar = esteira[line_mat][col_mat+2];

    while (!is_over && !passed && !is_blank)
    {  
        if (esteira[line_mat][col_mat] == '['){
            switch (lastChar)
            {
                case '>':
                    col_mat += 2; // +2 pq há espacos na matriz
                    break;
                case '<':
                    col_mat -= 2; // -2 pq há espacos na matriz
                    break;
                case '^':
                    line_mat -= 1; // sobe uma linha
                    break;
                case 'v':
                    line_mat += 1; // desce uma linha
                    break;
                default:
                    break;
            }
        }else
            checaEsteira(esteira, &line_mat, &col_mat, &lastChar); 
    }
    
    if(passed){
        printf("Loop infinito.\n");
        imprimeEsteira(esteira);
    }else if (is_blank){
        printf("Falha na esteira.\n");
        imprimeEsteira(esteira);
    }else if (is_over){
        printf("Ok.\n");
        imprimeEsteira(esteira);
    }
    return 0;
}

void imprimeEsteira(char esteira[][COLUNAS]){
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            printf("%c", esteira[i][j]); 
        }
    }
}


void checaEsteira (char esteira[LINHAS][COLUNAS], int *line_mat, int *col_mat, char *lastChar){
    switch (esteira[*line_mat][*col_mat])
    {
        case '>': 
        {
            *lastChar = '>'; // salva o char
            esteira[*line_mat][*col_mat] = '.'; // coloca . para representar que ja passou
            *col_mat += 2; //avanca para o proximo char
        } break;
        case '<': 
        {
            *lastChar = '<'; 
            esteira[*line_mat][*col_mat] = '.';
            *col_mat -= 2;
        } break;
        case '^': 
        {
            *lastChar = '^'; 
            esteira[*line_mat][*col_mat] = '.';
            *line_mat -= 1;
        } break;
        case 'v': 
        {
            *lastChar = 'v';
            esteira[*line_mat][*col_mat] = '.';
            *line_mat += 1;
        } break;
        case '#':
        {
            //caso haja uma juncao, verifica qual foi o ultimo char
            //para que continue seguindo o mesmo sentido de antes
            if (*lastChar == '>')
                *col_mat += 2;
            else if (*lastChar == '<')
                *col_mat -= 2;
            else if (*lastChar == '^')
                *line_mat -= 1;
            else if (*lastChar == 'v')
                *line_mat += 1;
        } break;
        // checa se a esteira terminou, se ja passou por ali
        // ou se ha falha
        case ']': is_over = true; break;
        case '.': passed = true; break;
        case ' ': is_blank = true; break;
        default: break;
    }
}