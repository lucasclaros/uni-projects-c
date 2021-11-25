#include "bignum.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


struct BigNum{
    bool negative;
    int maxPwrofTen;
    list_t *digits;
};

bignum_t *bignumRead(){
    bignum_t *n = malloc(sizeof(bignum_t));
    if(n == NULL) return NULL;
    n->negative = FALSE;
    n->maxPwrofTen = -1;
    n->digits = listCreate();

    char c;
    while ((c=getchar()) == '0');
    if(c == '-') 
    {
        n->negative = TRUE; 
        c=getchar();
    }
    while(c != ' ' && c != '\n')
    {
        if(c == '\r')
        {
            c=getchar();
            continue;
        }
        listInsert(n->digits, (c-48));
        n->maxPwrofTen++;
        c=getchar();
    }
    return n;
}

void bignumDestroy(bignum_t *n){
    listDestroy(n->digits);
    free(n);
}

char *readLine(bool *isEOF){
    int c,k=0;
    char *line = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        line = realloc(line, (k+1) * sizeof(char));
        line[k++] = c;
    }
    c = getchar();
    if (c == EOF) *isEOF = TRUE;
    else ungetc(c, stdin);

    line = realloc(line, (k+1) * sizeof(char));
    line[k] = '\0';
    return line;
}


void bignumSum(bignum_t *num1, bignum_t *num2){

    bignum_t *result = malloc(sizeof(bignum_t));
    result->negative = FALSE;
    result->digits = listSumNodes(num1->digits, num2->digits);

    result->maxPwrofTen = listGetSizelist(result->digits) - 1;
    listPrint(result->digits);
    printf("\n");
    bignumDestroy(result);
}

int bignumBigger(bignum_t *num1, bignum_t *num2){
    if (num1->negative && !num2->negative)
        return 0;
    else if (!num1->negative && num2->negative)
        return 1;
    if(num1->maxPwrofTen > num2->maxPwrofTen) 
        return 1;
    else if(num1->maxPwrofTen == num2->maxPwrofTen)
    {

        int result = listCompare(num1->digits, num2->digits);
        if(result == 1) return 1;
        else return 0;
    }
    else 
        return 0;
}

int bignumSmaller(bignum_t *num1, bignum_t *num2){
    if (num1->negative && !num2->negative)
        return 1;
    else if (!num1->negative && num2->negative)
        return 0;
    if(num1->maxPwrofTen < num2->maxPwrofTen) 
        return 1;
    else if(num1->maxPwrofTen == num2->maxPwrofTen)
    {
        int result = listCompare(num1->digits, num2->digits);
        if(result == 0 && !num1->negative) return 1;
        else return 0;
    }
    else 
        return 0;
}

int bignumEqual(bignum_t *num1, bignum_t *num2){
    if (!num1->negative && num2->negative)
        return 0;
    if(num1->maxPwrofTen != num2->maxPwrofTen) 
        return 0;
    else if(num1->maxPwrofTen == num2->maxPwrofTen)
    {
        int result = listCompare(num1->digits, num2->digits);
        if(result == -1) return 1;
        else return 0;
    }
}