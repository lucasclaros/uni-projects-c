#include "bignum.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool operationDecider();

int main(){
    int opNum;
    scanf("%d", &opNum); getchar(); 
    for (int i = 0; i < opNum; i++)
        operationDecider();
    return 0;
}

bool operationDecider(){
    bool isEOF = FALSE;
    char operation[4];
    scanf("%s", operation); getchar();
    bignum_t *num1 = bignumRead();
    bignum_t *num2 = bignumRead();

    if (strcmp(operation, "SUM") == 0)
    {
        bignumSum(num1, num2);
    }
    else if (strcmp(operation, "BIG") == 0)
    {
        int result = bignumBigger(num1, num2);
        printf("%d\n", result);
    }
    else if (strcmp(operation, "SML") == 0)
    {
        int result = bignumSmaller(num1, num2);
        printf("%d\n", result);
    }
    else if (strcmp(operation, "EQL") == 0)
    {
        int result = bignumEqual(num1, num2);
        printf("%d\n", result);
    }

    bignumDestroy(num1);
    bignumDestroy(num2);
    return isEOF;
}