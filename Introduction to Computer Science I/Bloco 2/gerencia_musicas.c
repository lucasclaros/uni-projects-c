#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//structs
typedef struct musica
{
    char *nome;
    char *artista;
    bool tocando;
    unsigned int duracao;
} Musica;

typedef struct playlist
{
    char *nome;
    int num_musicas;
    Musica musicas[15];
} Playlist;

//funcoes
char *read_line(char *);
void leComando(bool *, Playlist *);
void imprimePlaylist(Playlist *);
void addMusica(Playlist *);
void proxMusica(Playlist *);
void voltaMusica(Playlist *);

//começo
int main(){
    
    bool halt = false; //variavel de controle para finalização
    Playlist playlist;
    playlist.nome = calloc(1, sizeof(char));
    playlist.nome = read_line(playlist.nome);
    playlist.num_musicas = 0;

    //enquanto não encontrar o comando 5 (halt), lê os comandos
    do
    {
        leComando(&halt, &playlist);
    } while (!halt);
    
    //desalocacao
    free(playlist.nome);
    for (int i = 0; i < playlist.num_musicas; i++)
    {
        free(playlist.musicas[i].nome);
        free(playlist.musicas[i].artista);
    }
    return 0;
}

void leComando(bool *halt, Playlist *playlist){

    int comando;
    scanf("%d", &comando);
    getchar();
    
    switch (comando)
    {
    case 1:
        addMusica(playlist);
        break;
    case 2:
        imprimePlaylist(playlist);
        break;
    case 3:
        proxMusica(playlist);
        break;
    case 4:
        voltaMusica(playlist);
        break;
    case 5:
        *halt = true;
        break;
    default:
        break;
    }
}

char *read_line(char *linha){
    int c,k=0;
    while((c=getchar()) != '\n')
    {
        linha = realloc(linha, (k+2) * sizeof(char));
        linha[k++] = c;
    }
    linha[k] = '\0';
    return linha;
}

void addMusica(Playlist *playlist){
    if (playlist->num_musicas == 15)
        printf("Playlist cheia!\n");
    else
    {
        Musica novaMusica;
        novaMusica.nome = calloc(1, sizeof(char));
        novaMusica.artista = calloc(1, sizeof(char));
        novaMusica.nome = read_line(novaMusica.nome);
        novaMusica.artista = read_line(novaMusica.artista);
        //toca a primeira musica adicionada
        if (playlist->num_musicas == 0)
            novaMusica.tocando = true;
        else
            novaMusica.tocando = false;
        
        scanf("%d", &novaMusica.duracao);
        getchar();
        
        //adiciona a musica no vetor de musicas e incrementa a quantidade de musicas 
        playlist->musicas[playlist->num_musicas++] = novaMusica;
        printf("Musica %s de %s adicionada com sucesso.\n", novaMusica.nome, novaMusica.artista);
    }
}

void proxMusica(Playlist *playlist){
    int i;
    //i percorre as musicas até achar a que está tocando
    for (i = 0; playlist->musicas[i].tocando == false; i++); 
    playlist->musicas[i].tocando = false;
    playlist->musicas[i+1].tocando = true;
}

void voltaMusica(Playlist *playlist){
    int i;
    //i percorre as musicas até achar a que está tocando
    for (i = 0; playlist->musicas[i].tocando == false; i++);
    playlist->musicas[i].tocando = false;
    playlist->musicas[i-1].tocando = true;
}

void imprimePlaylist(Playlist *playlist){
    printf("---- Playlist: %s ----\n", playlist->nome);
    printf("Total de musicas: %d\n\n", playlist->num_musicas);
    //i percorre todas as músicas da playlist
    for (int i = 0; i < playlist->num_musicas; i++)
    {
        if (playlist->musicas[i].tocando)
            printf("=== NOW PLAYING ===\n");
        
        printf("(%d). '%s'\n", i+1, playlist->musicas[i].nome);
        printf("Artista: %s\n", playlist->musicas[i].artista);
        printf("Duracao: %d segundos\n\n", playlist->musicas[i].duracao);
    }
}