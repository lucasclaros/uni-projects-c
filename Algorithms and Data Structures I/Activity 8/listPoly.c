#include "listPoly.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Polys
{
    int numPol;
    list_t **polynomials;
    list_t *finalPoly;
};

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n' && c != EOF)
    {
        if (c == '\r') continue;
        
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}


poly_t *polynomialCreate(int numPol){
    poly_t *p = malloc(sizeof(poly_t));
    assert(p != NULL);

    p->polynomials = malloc(numPol * sizeof(list_t *));
    assert(p->polynomials != NULL);
    p->finalPoly = listCreate();
    assert(p->finalPoly != NULL);
    p->numPol = numPol;

    return p;
}


void polynomialRead(poly_t *p, int index){
    char c = getchar(); // ignore '\n'
    p->polynomials[index] = listCreate();
    while ((c = getchar()) != ')')
    {
        int coef;
        scanf(" %d", &coef); 
        listInsert(p->polynomials[index], coef);
    }
    getchar();
}

void polynomialDestroy(poly_t *p){
    for (int i = 0; i < p->numPol; i++)
        listDestroy(p->polynomials[i]);
    listDestroy(p->finalPoly);
    free(p->polynomials);
    free(p);
}

void polynomialSum(poly_t *p){
    for (int i = 0; i < p->numPol; i++)
        listSumNodes(p->polynomials[i], p->finalPoly);
}

void printFinalPoly(poly_t *p){
    printf("(");
    listPrint(p->finalPoly);
    printf(")\n");
}