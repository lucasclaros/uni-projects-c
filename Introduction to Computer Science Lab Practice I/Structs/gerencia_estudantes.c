#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dados_aluno
{
    int n_usp;
    char *nome;
    char *curso;
    int idade;
} Aluno;

typedef struct registro_geral
{
    Aluno *alunos;
    int qtd_alunos;
} Registro;

char *read_line(char *);
void registraAluno(Registro *);
void leComando(Registro *);
void consulta_nusp(Registro *, int);
void consulta_curso(Registro *, char *);
void imprimeRegistro(Registro *);
void imprimeAluno(Registro *, int);

int main(){
    char c;
    Registro registro;
    registro.alunos = NULL;
    registro.qtd_alunos = 0;
    while ((c=getchar()) != '-')
    {
        ungetc(c, stdin);
        registraAluno(&registro);
    }
    getchar();
    getchar();
    while ((c=getchar()) != '-')
    {
        ungetc(c, stdin);
        leComando(&registro);
    }
    for (int i = 0; i < registro.qtd_alunos; i++)
    {
        free(registro.alunos[i].nome);
        free(registro.alunos[i].curso);
    }
    free(registro.alunos);
    return 0;
}

void registraAluno(Registro *registro){
    Aluno novo_aluno;
    scanf("%d ", &novo_aluno.n_usp);
    novo_aluno.nome = read_line(novo_aluno.nome);
    novo_aluno.curso = read_line(novo_aluno.curso);
    scanf("%d ", &novo_aluno.idade);
    registro->alunos = realloc(registro->alunos, (registro->qtd_alunos+1)*sizeof(Aluno));
    registro->alunos[registro->qtd_alunos++] = novo_aluno;
}

void leComando(Registro *registro){
    int comando=0;
    scanf("%d", &comando);
    getchar();
    switch (comando)
    {
        case 1:
        {
            int n_usp;
            scanf("%d ", &n_usp);
            consulta_nusp(registro, n_usp);
            break;
        }
        case 2:
        {
            char *curso=NULL;
            curso = read_line(curso);
            consulta_curso(registro, curso);
            free(curso);
            break;
        }
        case 3:
            imprimeRegistro(registro);
            break;
        
        default:
            break;
    }
}

void consulta_nusp(Registro *registro, int n_usp){
    for (int i = 0; i < registro->qtd_alunos; i++)
        if (registro->alunos[i].n_usp == n_usp)
            imprimeAluno(registro, i);
}

void consulta_curso(Registro *registro, char *curso){
    for (int i = 0; i < registro->qtd_alunos; i++)
        if (!(strcmp(registro->alunos[i].curso, curso)))
            imprimeAluno(registro, i);
}

void imprimeRegistro(Registro *registro){
    for (int i = 0; i < registro->qtd_alunos; i++)
        imprimeAluno(registro, i);
}

void imprimeAluno(Registro *registro, int pos_aluno){
    printf("Nome: %s\n", registro->alunos[pos_aluno].nome);
    printf("Curso: %s\n", registro->alunos[pos_aluno].curso);
    printf("N USP: %d\n", registro->alunos[pos_aluno].n_usp);
    printf("IDADE: %d\n\n", registro->alunos[pos_aluno].idade);
}

char *read_line(char *linha){
    int c,k=0;
    linha = calloc(1, sizeof(char));
    while((c=getchar()) != '\n' && c != 36)
    {
        linha = realloc(linha, (k+2) * sizeof(char));
        linha[k++] = c;
    }
    linha[k] = '\0';
    return linha;
}