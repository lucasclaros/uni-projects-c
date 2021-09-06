/*    
 * Book Activity: log base 2
 * Lucas da S. Claros - 12682592
 * Course: SCC0201 
 */

#include <stdio.h>
 

/*
 *   
 *
 */
int log2(int n){
    if(n < 2)
        return 0;
    else return 1 + lg(n/2);
}

int main(){
    int number;
    scanf("%d", &number);
    number = log2(number);
    printf("%d\n", number);
    return 0;
}

