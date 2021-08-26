#include <stdio.h>
#include <stdlib.h>

double leExpressoes();

int main(){
    char c;
    while ((c=getchar()) != EOF)
    {
        if (c == ')' || c == '\n')
        {       
            while (c != '\n')
                c = getchar();
            c = getchar();
        }
        if (c == EOF)
            return 0;
        ungetc(c, stdin);
        double teste = leExpressoes();
        printf("%lf\n", teste);
    }
    return 0;
}

double leExpressoes(){
    char character = getchar(), c1, c2;
    double numero1=0, numero2=0;
    switch (character)
    {
        case '(':
        {
            double resultado = leExpressoes();
            return resultado;
        }
        case '+':
        {
            getchar();
            c1 = getchar();
            if (c1 == '(')
                numero1 = leExpressoes();
            else
            {
                ungetc(c1, stdin);
                scanf(" %lf", &numero1);
                getchar();
            }
            c2 = getchar();
            if (c2 == ' ')
                c2 = getchar(); 
            if (c2 == '(')
                numero2 = leExpressoes();
            else if (c2 == ')')
            {
                getchar();
                scanf("%lf", &numero2);
                getchar();
            }
            else
            {
                ungetc(c2, stdin);
                scanf(" %lf", &numero2);
                getchar();
            } 
            return numero1+numero2;
        }
        case '-':
        {
            getchar();
            c1 = getchar();
            if (c1 == '(')
                numero1 = leExpressoes();
            else
            {
                ungetc(c1, stdin);
                scanf(" %lf", &numero1);
                getchar();
            }
            c2 = getchar();
            if (c2 == ' ')
                c2 = getchar(); 
            if (c2 == '(')
                numero2 = leExpressoes();
            else if (c2 == ')')
            {
                getchar();
                scanf("%lf", &numero2);
                getchar();
            }
            else
            {
                ungetc(c2, stdin);
                scanf(" %lf", &numero2);
                getchar();
            } 
            return numero1-numero2;
        }
        case '*':
        {
            getchar();
            c1 = getchar();
            if (c1 == '(')
                numero1 = leExpressoes();
            else
            {
                ungetc(c1, stdin);
                scanf(" %lf", &numero1);
                getchar();
            }
            c2 = getchar();
            if (c2 == ' ')
                c2 = getchar(); 
            if (c2 == '(')
                numero2 = leExpressoes();
            else if (c2 == ')')
            {
                getchar();
                scanf("%lf", &numero2);
                getchar();
            }
            else
            {
                ungetc(c2, stdin);
                scanf(" %lf", &numero2);
                getchar();
            } 
            return numero1*numero2;
        }
        case '/':
        {
            getchar();
            c1 = getchar();
            if (c1 == '(')
                numero1 = leExpressoes();
            else
            {
                ungetc(c1, stdin);
                scanf(" %lf", &numero1);
                getchar();
            }
            c2 = getchar();
            if (c2 == ' ')
                c2 = getchar(); 
            if (c2 == '(')
                numero2 = leExpressoes();
            else if (c2 == ')')
            {
                getchar();
                scanf("%lf", &numero2);
                getchar();
            }
            else
            {
                ungetc(c2, stdin);
                scanf(" %lf", &numero2);
                getchar();
            } 
            return numero1/numero2;
        }
        default:
        {
            ungetc(character, stdin);
            double resultado;
            scanf(" %lf", &resultado);
            return resultado;
        }
    }
}