#include <stdio.h>

long int x,y,l1,a1,x2,y2,l2,a2;
long int largura1, altura1, largura2, altura2;
int main() {
    scanf("%ld %ld %ld %ld", &x,&y,&l1,&a1);
    scanf("%ld %ld %ld %ld", &x2,&y2,&l2,&a2);

    largura1 = x+l1; //ponto da largura final do retangulo 1
    altura1 = y+a1; //ponto da altura final do retangulo 1
    largura2 = x2+l2; //ponto da largura final do retangulo 2
    altura2 = y2+a2; //ponto da altura final do retangulo 2

    /*
        tomo como base o primeiro x e y como coordenadas fixas e a partir daí
        checo onde o x2,y2 está em relação a eles
    */

    if(x2 >= x && x2 <= largura1){
        if(y2 > altura1 || altura2 < y){
            printf("MISS");    
        }else if(a2 == 0){
            printf("HIT: %ld %ld %ld %d",x2,y2,(l1-(x2-x)),0);
        }else if(y2 >= y && y2 <= altura1){
             if(largura2 <= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y2,(l2),(a2));
            }else if(largura2 >= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y2,(l1-(x2-x)),(a1-(y2-y)));
            }else if(largura2 >= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y2,(l1-(x2-x)),(a2));
            }else if(largura2 <= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y2,(l2),(a1-(y2-y)));
            }
        }else if(y2 <= y && y <= altura2){
            if(largura2 <= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y,(l2),(a2-(y-y2)));
            }else if(largura2 >= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y,(l1-(x2-x)),(a1));
            }else if(largura2 >= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y,(l1-(x2-x)),(a2-(y-y2)));
            }else if(largura2 <= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x2,y,(l2),(a1));
            }
        }
    }else if(x2 <= x && x <= largura2){
        if(y2 > altura1 || altura2 < y){
            printf("MISS");    
        }else if(l2 == 0){
            printf("HIT: %ld %ld %d %ld",x,y,0,(a2-(y-y2)));
        }else if(y2 <= y && y <= altura2){
            if(largura2 <= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y,(l2-(x-x2)),(a2-(y-y2)));
            }else if(largura2 >= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y,(l1),(a1));
            }else if(largura2 >= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y,(l1),(a2-(y-y2)));
            }else if(largura2 <= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y,(l2-(x-x2)),(a1));
            }
        }else if(y2 >= y && y2 <= altura1){
            
            if(largura2 <= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y2,(l2-(x-x2)),(a2));
            }else if(largura2 >= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y2,(l1),(a1-(y2-y)));
            }else if(largura2 >= largura1 && altura2 <= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y2,(l1),(a2));
            }else if(largura2 <= largura1 && altura2 >= altura1){
                printf("HIT: %ld %ld %ld %ld",x,y2,(l2-(x-x2)),(a1-(y2-y)));
            }
        }
    }else{
        printf("MISS");
    }
    
}