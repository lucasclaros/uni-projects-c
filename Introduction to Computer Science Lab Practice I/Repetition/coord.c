#include <stdio.h>

int x = 0, y = 0;
char a[6];
int main() {
    for(int i = 0; i < 6; i++){
        scanf("%c", &a[i]);
        switch(a[i]){
            case 'W': 
                y += 1;
                break;
            case 'S': 
                y -= 1;
                break;
            case 'A': 
                x -= 1;
                break;
            case 'D': 
                x += 1;
                break;
        }
    }
    printf("%i %i", x, y);
    return 0;
}
