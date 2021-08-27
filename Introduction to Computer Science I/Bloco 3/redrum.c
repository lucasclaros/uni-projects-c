#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct frase
{
    char *frase;
    int resultado; //-1 = indireto, 1 = direto e 0 = nao palindromo
    bool end;
} Frase;


char *read_line (char *);
void is_palindrome(Frase *, int, int);

int main(){
    Frase frase;
    frase.frase = NULL;
    frase.resultado=0;
    frase.end = false;
    frase.frase = read_line(frase.frase);
    is_palindrome(&frase, 0, strlen(frase.frase)-1);

    if (frase.resultado > 0)
        printf("Palindromo direto\n");
    else if (frase.resultado < 0)
        printf("Palindromo indireto\n");
    else 
        printf("Nao eh um palindromo\n");

    free(frase.frase);
    return 0;
}

//A ideia é comparar a primeira com ultima letra e ir verificando até que se chegue ao meio da palavra

void is_palindrome(Frase *frase, int indice_comeco, int indice_final){
    if (indice_comeco >= indice_final)
        frase->end = true;
    if (!frase->end)
    {
        char comeco = tolower(frase->frase[indice_comeco]);
        char final = tolower(frase->frase[indice_final]);
        if (isalnum(comeco) == 0 && comeco != ' ' && comeco != '/')
        {
            indice_comeco++;
            comeco = tolower(frase->frase[indice_comeco]);
        }
        if (isalnum(final) == 0 && final != ' ' && final != '/')
        {
            indice_final--;
            final = tolower(frase->frase[indice_final]);
        }
        if (comeco == final)
        {
            //uma vez que a frase foi dada como palindromo indireto, ela nao pode ser um palindromo direto mais
            if (frase->resultado != -1)
                frase->resultado = 1;
            is_palindrome(frase, indice_comeco+1, indice_final-1);
        }else
        {
            //se os caracteres são diferentes mas um deles é espaço ou barra continua verificando
            //se tudo der certo, a frase é um palindromo indireto
            if (comeco == ' ' || comeco == '/')
            {
                is_palindrome(frase, indice_comeco+1, indice_final);
                frase->resultado = -1;
            }
            else if (final == ' ' || final == '/')
            {
                is_palindrome(frase, indice_comeco, indice_final-1);
                frase->resultado = -1;
            }
            else
                frase->resultado = 0;
        }
    }
    return;
}

char *read_line(char *linha){
    int c, k=0;
    linha = calloc(1, sizeof(char));
    while ((c=getchar()) != '\n')
    {
        linha = realloc(linha, (k+2)*sizeof(char));
        linha[k++] = c;
    }
    linha[k] = '\0';
    return linha;
}