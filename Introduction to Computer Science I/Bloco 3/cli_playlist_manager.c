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
void binaryToNum(char *);
char *read_line(char *);
void leComando(bool *, Playlist *);
void imprimePlaylist(Playlist *);
void addMusica(Playlist *);
void proxMusica(Playlist *);
void voltaMusica(Playlist *);
void salvaPlaylist(Playlist *);
void carregaPlaylist(Playlist *, bool *);
void serializaDados(Playlist *, char *);
void addMusicaDisco(Playlist *, FILE *);

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
    for (int i = 0; i < playlist.num_musicas && playlist.num_musicas > 0; i++)
    {
        free(playlist.musicas[i].nome);
        free(playlist.musicas[i].artista);
    }
    return 0;
}


void leComando(bool *halt, Playlist *playlist){

    int comando;
    scanf("%i", &comando);
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
        salvaPlaylist(playlist);
        break;
    case 6:
        carregaPlaylist(playlist, halt);
        break;
    case 7:
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

void salvaPlaylist(Playlist *playlist){
    char *nomeArquivo = calloc(1, sizeof(char));
    nomeArquivo = read_line(nomeArquivo);
    serializaDados(playlist, nomeArquivo);
    printf("Playlist %s salva com sucesso.\n", nomeArquivo);
    binaryToNum(nomeArquivo);
    free(nomeArquivo);
}

void carregaPlaylist(Playlist *playlist, bool *halt){
    char *nomePlaylist = calloc(1, sizeof(char));
    nomePlaylist = read_line(nomePlaylist);
    FILE *playlistSalva = fopen(nomePlaylist, "rb");
    if (playlistSalva == NULL){
        printf("Arquivo %s nao existe.\n", nomePlaylist);
        *halt = true;
        free(nomePlaylist);
    }else{
        int tamanhoNomePlaylist=0;
        fread(&tamanhoNomePlaylist, sizeof(int), 1, playlistSalva);
        free(playlist->nome);
        playlist->nome = calloc(tamanhoNomePlaylist+1, sizeof(char));
        fread(playlist->nome, sizeof(char), tamanhoNomePlaylist, playlistSalva);
        playlist->nome[tamanhoNomePlaylist] = '\0';
        fread(&playlist->num_musicas, sizeof(int), 1, playlistSalva);
        addMusicaDisco(playlist, playlistSalva);
        printf("Playlist %s carregada com sucesso.\n", nomePlaylist);
        binaryToNum(nomePlaylist);
        fclose(playlistSalva);
        free(nomePlaylist);
    }
}

void serializaDados(Playlist *playlist, char *nomeArquivo){
    FILE *cabecalhoPlaylist = fopen(nomeArquivo, "wb");

    int tamanhoNomePlaylist = strlen(playlist->nome);
    int num_musicas = playlist->num_musicas;

    fwrite(&tamanhoNomePlaylist, sizeof(int), 1, cabecalhoPlaylist);
    fwrite(playlist->nome, sizeof(char), tamanhoNomePlaylist, cabecalhoPlaylist);
    fwrite(&num_musicas, sizeof(int), 1, cabecalhoPlaylist);

    fclose(cabecalhoPlaylist);
    FILE *registrosPlaylist = fopen(nomeArquivo, "ab");

    for (int indice=0; indice < playlist->num_musicas; indice++)
    {
        int tamanhoNomeMusica = strlen(playlist->musicas[indice].nome);
        int tamanhoNomeArtista = strlen(playlist->musicas[indice].artista);

        fwrite(&tamanhoNomeMusica, sizeof(int), 1, registrosPlaylist);
        fwrite(playlist->musicas[indice].nome, sizeof(char), tamanhoNomeMusica, registrosPlaylist);
        fwrite(&tamanhoNomeArtista, sizeof(int), 1, registrosPlaylist);
        fwrite(playlist->musicas[indice].artista, sizeof(char), tamanhoNomeArtista, registrosPlaylist);
        fwrite(&playlist->musicas[indice].duracao, sizeof(int), 1, registrosPlaylist);
    }

    fclose(registrosPlaylist);
}

void addMusicaDisco(Playlist *playlist, FILE *playlistSalva){
    for (int indiceMusicas = 0; indiceMusicas < playlist->num_musicas; indiceMusicas++)
    {
        Musica novaMusica;
        int tamanhoNomeMusica=0, tamanhoNomeArtista=0;
        fread(&tamanhoNomeMusica, sizeof(int), 1, playlistSalva);
        novaMusica.nome = calloc(tamanhoNomeMusica+1, sizeof(char));
        fread(novaMusica.nome, sizeof(char), tamanhoNomeMusica, playlistSalva);
        novaMusica.nome[tamanhoNomeMusica] = '\0';
        fread(&tamanhoNomeArtista, sizeof(int), 1, playlistSalva);
        novaMusica.artista = calloc(tamanhoNomeArtista+1, sizeof(char));
        fread(novaMusica.artista, sizeof(char), tamanhoNomeArtista, playlistSalva);
        novaMusica.artista[tamanhoNomeArtista] = '\0';
        fread(&novaMusica.duracao, sizeof(int), 1, playlistSalva);
        //toca a primeira musica adicionada
        if (indiceMusicas == 0)
            novaMusica.tocando = true;
        else
            novaMusica.tocando = false;
        //adiciona a musica no vetor de musicas
        playlist->musicas[indiceMusicas] = novaMusica;
    }
}

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");
    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }
    fclose(fp);
    printf("%lf\n", binValue);
}