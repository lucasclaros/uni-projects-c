#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct dados_arquivo
{
    char *nome_arquivo;
    char **matriz;
    char preenchimento;
    char cor_anterior;
    int qtd_regioes;
    bool is_EOF;
    int qtd_linhas;
} Desenho;

char *read_line();
char *read_line_arquivo(FILE *, bool *);
void leRegioes(Desenho *);
void leDesenho(Desenho *);
void preencheDesenho(Desenho *, int, int, char, char);
void imprimeDesenho(Desenho *);
void escreveArquivo(Desenho *);
void enquadra_arte(char *, int, int);

int main(){
    Desenho desenho;
    desenho.qtd_linhas=0;
    desenho.is_EOF = false;
    desenho.nome_arquivo = NULL;
    desenho.nome_arquivo = read_line();

    leDesenho(&desenho);
    leRegioes(&desenho);

    for (int i = 0; i < desenho.qtd_linhas; i++)
        free(desenho.matriz[i]);
    free(desenho.matriz);
    free(desenho.nome_arquivo);
    return 0;
}

void leDesenho(Desenho *desenho){
    desenho->matriz = NULL;
    FILE *arquivo = fopen(desenho->nome_arquivo, "r");
    while (!desenho->is_EOF)
    {
        desenho->matriz = realloc(desenho->matriz, (desenho->qtd_linhas+1)*sizeof(char *));
        desenho->matriz[desenho->qtd_linhas] = NULL;
        desenho->matriz[desenho->qtd_linhas] = read_line_arquivo(arquivo, &desenho->is_EOF);
        desenho->qtd_linhas++;
    }
    fclose(arquivo);
    printf("Arte inicial:\n");
    imprimeDesenho(desenho);
}

void leRegioes(Desenho *desenho){
    int pos_x, pos_y;
    scanf("%d", &desenho->qtd_regioes);
    getchar();
    for (int i = 0; i < desenho->qtd_regioes; i++)
    {
        scanf("%c %d %d", &desenho->preenchimento, &pos_x, &pos_y);
        getchar();
        desenho->cor_anterior = desenho->matriz[pos_x][pos_y];
        preencheDesenho(desenho, pos_x, pos_y, desenho->preenchimento, desenho->cor_anterior);
        printf("Arte apos a etapa %d:\n", i);
        imprimeDesenho(desenho);
    }
    escreveArquivo(desenho);
    printf("Arte enquadrada:\n");
    enquadra_arte(desenho->nome_arquivo, desenho->qtd_linhas, strlen(desenho->matriz[0]));
}

void escreveArquivo(Desenho *desenho){
    FILE *novo_arquivo = fopen(desenho->nome_arquivo, "w");
    for (int i = 0; i < desenho->qtd_linhas; i++)
    {
        fprintf(novo_arquivo, "%s", desenho->matriz[i]);
        if (i+1 != desenho->qtd_linhas) //se não for a ultima linha, add \n no final
            fprintf(novo_arquivo, "%c", '\n');
    }
    fclose(novo_arquivo);
}

/*
    Se a posicao checada for igual à cor que estava antes de pintar, pinta a posicao
    
    Checa se as posicoes (baixo, cima, direita, esquerda) estão dentro da matriz e se
    são iguais à cor anterior
*/
void preencheDesenho(
    Desenho *desenho, 
    int pos_x, 
    int pos_y, 
    char preenchimento, 
    char cor_anterior
){
    if (desenho->matriz[pos_x][pos_y] == cor_anterior)
        desenho->matriz[pos_x][pos_y] = preenchimento;   
    if (pos_x+1 < desenho->qtd_linhas && desenho->matriz[pos_x+1][pos_y] == cor_anterior)
        preencheDesenho(desenho, pos_x+1, pos_y, preenchimento, cor_anterior);
    if (pos_x-1 >= 0 && desenho->matriz[pos_x-1][pos_y] == cor_anterior)
        preencheDesenho(desenho, pos_x-1, pos_y, preenchimento, cor_anterior);
    if (pos_y+1 < strlen(desenho->matriz[0]) && desenho->matriz[pos_x][pos_y+1] == cor_anterior)
        preencheDesenho(desenho, pos_x, pos_y+1, preenchimento, cor_anterior);
    if (pos_y-1 >= 0 && desenho->matriz[pos_x][pos_y-1] == cor_anterior)
        preencheDesenho(desenho, pos_x, pos_y-1, preenchimento, cor_anterior);
}

void imprimeDesenho(Desenho *desenho){
    for (int i = 0; i < desenho->qtd_linhas; i++)
        printf("%s\n", desenho->matriz[i]);
    printf("\n");
}

char *read_line_arquivo(FILE *arquivo, bool *is_EOF){
    int c,k=0;
    char *linha = NULL;
    while((c=fgetc(arquivo)) != EOF && c != '\n')
    {
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    c == EOF ? *is_EOF = true : 0;
    return linha;
}

char *read_line(){
    int c,k=0;
    char *linha = NULL;
    while((c=getchar()) != '\n')
    {
        linha = realloc(linha, (k+1) * sizeof(char));
        linha[k++] = c;
    }
    linha = realloc(linha, (k+1) * sizeof(char));
    linha[k] = '\0';
    return linha;
}


void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro
) {
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}