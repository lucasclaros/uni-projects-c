#include <stdio.h>
#include <stdlib.h>

void leEntradaJit(FILE *);

int main(){
    FILE *arquivo = fopen("jit.c", "w");
    fprintf(arquivo, "%s\n", "#include <stdio.h>");
    fprintf(arquivo, "%s\n", "#define MEM_SIZE 30000");
    fprintf(arquivo, "%s\n", "int main(){");
    fprintf(arquivo, "\t%s\n", "char mem[MEM_SIZE]; int i = 0;");
    fprintf(arquivo, "\t%s\n", "for (int j = 0; j < MEM_SIZE; j++){ mem[j] = 0; }");
    leEntradaJit(arquivo);
    fprintf(arquivo, "\t%s\n", "printf(\"\\n\");");
    fprintf(arquivo, "\t%s\n", "for (int j = 0; j < MEM_SIZE; j++)");
    fprintf(arquivo, "\t\t%s\n", "if (mem[j] != 0)");
    fprintf(arquivo, "\t\t\t%s\n", "printf(\"%d \", mem[j]);");
    fprintf(arquivo, "%s\n", "printf(\"\\n\");");
    fprintf(arquivo, "%s\n", "return 0;");
    fprintf(arquivo, "%c", '}');
    fclose(arquivo);
    system("gcc ./jit.c -o jit-exe"); 
    system("./jit-exe");
    return 0;
}

void leEntradaJit(FILE *arquivo){
    int c;
    while ((c=getchar()) != EOF)
    {
        switch (c)
        {
        case '+':
            fprintf(arquivo, "\t%s\n", "mem[i]++;");
            break;
        case '-':
            fprintf(arquivo, "\t%s\n", "mem[i]--;");
            break;
        case '>':
            fprintf(arquivo, "\t%s\n", "i++;");
            break;
        case '<':
            fprintf(arquivo, "\t%s\n", "i--;");
            break;
        case '.':
            fprintf(arquivo, "\t%s\n", "putchar(mem[i]);");
            break;
        case '[':
            fprintf(arquivo, "\t%s\n", "while(mem[i]){");
            break;
        case ']':
            fprintf(arquivo, "\t%c\n", '}');
            break;
        default:
            break;
        }
    }
    

}