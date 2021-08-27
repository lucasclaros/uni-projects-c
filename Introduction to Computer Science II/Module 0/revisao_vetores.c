#include <stdio.h>
#include <stdlib.h>

int main(){
    int **numbers = calloc(1, sizeof(int *)), values=0, current_number;
    numbers[0] = calloc(2, sizeof(int));

    scanf(" %d", &numbers[values][0]);
    numbers[values++][1]++;
    
    while(scanf(" %d", &current_number) != EOF)
    {
        int presence = 0;

        //i percorre o vetor
        //se o número já estiver presente, incrementa segunda coluna (frequencia)
        for (int i = 0; i < values; i++)
        {
            if (numbers[i][0] == current_number)
            {
                numbers[i][1]++;
                presence = 1;
            }
        }
        //percorrido o vetor e não encontrado o valor, adiciona-o no vetor
        if (!presence)
        {
            numbers = realloc(numbers, (values+1)*sizeof(int *));
            numbers[values] = calloc(2, sizeof(int));
            numbers[values][0] = current_number;
            numbers[values++][1]++;
        }
    }

    for (int i = 0; i < values; i++)
        printf("%d (%d)\n", numbers[i][0], numbers[i][1]);
    
    for (int i = 0; i < values; i++)
        free(numbers[i]);
    free(numbers);
    return 0;
}