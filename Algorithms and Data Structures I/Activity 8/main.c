#include "listPoly.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int cases;
    scanf("%d", &cases); getchar();
    for (int i = 0; i < cases; i++)
    {
        int numPol;
        scanf("%d", &numPol); getchar();
        poly_t *p = polynomialCreate(numPol);

        for (int j = 0; j < numPol; j++)
            polynomialRead(p, j);

        polynomialSum(p);
        printFinalPoly(p);
        polynomialDestroy(p);
    }
    return 0;
}