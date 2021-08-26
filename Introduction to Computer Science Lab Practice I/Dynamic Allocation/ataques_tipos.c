#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int qtd_tipos;
    scanf("%d", &qtd_tipos);

    float **relacao_tipos = calloc(qtd_tipos, sizeof(float *));
    for (int i=0; i < qtd_tipos; i++)
        relacao_tipos[i] = calloc(qtd_tipos, sizeof(float));

    for (int i=0; i < qtd_tipos; i++)
        for (int j=0; j < qtd_tipos; j++)
            scanf(" %f", &relacao_tipos[i][j]);

    int poder_ataque=0, indice_tabela=0, **ataques=NULL, qtd_ataques=0;
    bool is_over = false;
    do {
        scanf(" %d", &poder_ataque);
        if (poder_ataque == -1)
            is_over = true;
        else 
        {
            scanf(" %d", &indice_tabela);
            ataques = realloc(ataques, (qtd_ataques+1) * sizeof(int *));
            ataques[qtd_ataques] = calloc(2, sizeof(int));
            ataques[qtd_ataques][0] = poder_ataque;
            ataques[qtd_ataques][1] = indice_tabela;
            qtd_ataques++;
        }
    }while(!is_over);

    int tipo_inimigo, tipo_aliado, ataque_aliado, melhor_ataque;
    float dano_atual, melhor_dano=0;
    scanf(" %d", &tipo_inimigo);

    for (int indice=0; indice < qtd_ataques; indice++)
    {
        ataque_aliado = ataques[indice][0];
        tipo_aliado = ataques[indice][1];
        dano_atual = (float)ataque_aliado * relacao_tipos[tipo_aliado][tipo_inimigo];
        if (dano_atual > melhor_dano)
        {
            melhor_ataque = indice;
            melhor_dano = dano_atual;
        }
    }
    printf("O melhor ataque possui indice %d e dano %.2f\n", melhor_ataque, melhor_dano);

    for (int i=0; i < qtd_ataques; i++)
        free(ataques[i]);
    for (int i=0; i < qtd_tipos; i++)
        free(relacao_tipos[i]);
    free(ataques);
    free(relacao_tipos);
    return 0;
}