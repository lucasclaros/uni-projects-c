#include <stdio.h>

#define QTD_ENTRADA 25
#define QTD_TONS 5

int main() {
    int entrada[QTD_ENTRADA]={}, cor[QTD_TONS][1]={};
    for(int i=0; i < QTD_ENTRADA; i++)
    {
        scanf("%d", &entrada[i]);
        //checa qual cor foi lida e adiciona na linha correspondente da matriz cor
        switch(entrada[i])
        {
            case 0: cor[0][0]++; break;
            case 1: cor[1][0]++; break;
            case 2: cor[2][0]++; break;
            case 3: cor[3][0]++; break;
            case 4: cor[4][0]++; break;
        }
    }

    //i percorre as cores
    for(int i = 0; i < QTD_TONS; i++)
    {
        printf("%d: |", i);
        //j percorre a quantidade que a cor apareceu
        for(int j = 0; j < cor[i][0]; j++)
            printf("#");
        printf("\n");
    }

    int indice, moda = cor[0][0];
    //i percorre as cores 
    for(int i = 0; i < QTD_TONS; i++)
        //se existir algum numero maior que o anterior
        //atualiza a moda e pega o indice da cor
        if(moda <= cor[i][0]){ moda = cor[i][0]; indice = i; }

    //i percorre as cores, se o valor da entrada for igual ao da moda, printa o valor
    for(int i = 0; i < QTD_ENTRADA; i++)
        if(entrada[i] == indice) printf("%d\n", i);
    
    return 0;
}