/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 03/10/2021 15:05
 *   Modified time: 09/10/2021 18:42
 *   Description: Balanced Sequence
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "commands.h"

int main(){
    bool isEOF = FALSE;
    while (!isEOF)
    {
        char *sequence = read_line(&isEOF);
        stack_t *s = create();
        for (int i = 0; sequence[i] != '\0'; i++)
        { 
            int index = getClosingBracketIndex(sequence[i]);

            if(isaOpeningBracket(sequence[i])) 
                push(s, sequence[i]);
            else if(index != -1)
            {
                if(checkLastCharAdded(top(s), index))
                    pop(s);
                else
                    push(s, sequence[i]); 
            }else if(top(s) == '"')
                pop(s);
            else
                push(s, sequence[i]);
        }
        checkSequence(s);
        destroy(s);
        free(sequence);
    }
    return 0;
}