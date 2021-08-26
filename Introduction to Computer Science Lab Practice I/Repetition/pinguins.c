#include <stdio.h>

int main() {
    int rodadas = 0, jogadores = 0, pos = 0, fila = 1;
    scanf("%d %d %d", &rodadas, &jogadores, &pos);
    
    for(int i = 1; fila <= rodadas; i++){
        //for para impressao da frase "x pinguins"
        for(int j = 0; j < i; j++){
            //checa se é a vez de pingu falar
            if(fila <= rodadas && fila == pos){
                //se sim, a posicao e alterada
                if(i == 1){
                    printf("%d pinguim\n", i);
                    pos += jogadores;
                }else{
                    printf("%d pinguins\n", i);
                    pos += jogadores;
                }
            }
            //a cada final de execucao a fila move(proxima pessoa)
            fila++;
        }
        //for para impressao da frase "no gelo"
        for(int j = 0; j < i; j++){
            if(fila <= rodadas && fila == pos){
                printf("no gelo\n");
                pos += jogadores;
            }
            fila++;
        }
        //for para impressao da frase "uhuu!"
        for(int j = 0; j < i; j++){
            if(fila <= rodadas && fila == pos){
                printf("uhuu!\n");
                pos += jogadores;
            }
            fila++;
        }
    }
    return 0;
}
