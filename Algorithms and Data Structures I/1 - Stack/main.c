/**
 *   Author: Lucas da Silva Claros
 *   nUSP: 12682592
 *   Create Time: 06/09/2021 15:50
 *   Modified time: 17/09/2021 01:59
 *   Description: 
 *      Learning about Stack with decimal to binary conversion
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack_t *convertToBinary(int);

int main(){

    int decimal;
    scanf("%d", &decimal);
    stack_t *binary = convertToBinary(decimal);
    printStack(binary);
    destroy(binary);
    return 0;
}


stack_t *convertToBinary(int decimal){
    stack_t *p;
    p = create();
    while (decimal >= 2)
    {
        elem reminder;
        reminder = decimal % 2;
        push(p, reminder);
        decimal = decimal / 2;
    }
    push(p, decimal);
    return p;
}