/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 03/10/2021 15:05
 *   Modified time: 03/10/2021 17:26
 *   Description: Balanced Sequence
 */

#include "commands.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    stack_t *s = create();
    bool isEOF = checkSequence(s); 

    if (isEmpty(s))
        printf("BALANCEADO");
    else
        printf("NÃO BALANCEADO");

    destroy(s);
    return 0;
}