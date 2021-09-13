/*    
 * Book Activity: log base 2
 * Lucas da S. Claros - 12682592
 * Course: SCC0201 
 *   Modified time: 13/09/2021 01:17
*/
#include <stdio.h>


int main(){
    char teste[3][6] = {'a','b','c','d','e','t',
                        'f','g','h','i','j','p',
                        '1','2','3','4','5','6'};

    for (int i = 0; i < 18; i++)
    {
        int row = i / 6;
        int col = i % 6;
        printf("%c ", teste[row][col]);
    }
    

    return 0;
}

