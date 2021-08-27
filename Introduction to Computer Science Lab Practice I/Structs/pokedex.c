#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct atributos
{
    int hp;
    int ataque;
    int defesa;
    int atk_especial;
    int def_especial;
    int velocidade;
} Atributos;

typedef struct ataques
{
    char nome[20];
    int poder_base;
    float acuracia;
    char classe;
} Ataques;


typedef struct pokemon
{
    char nome[50];
    char primario[20];
    char secundario[20];
    Atributos atributos;
    Ataques ataques[4];
} Pokemon;

typedef struct pokedex
{
    Pokemon *pokemons;
    int qtd_pokemons;
    bool halt;
} Pokedex;


void leComandos(Pokedex *);
void cadastroPokemon(Pokedex *);
void addAtaque(Pokedex *);
void imprimePokemon(Pokedex *);
void imprimeAtaque(Pokedex *);

int main(){
    Pokedex pokedex;
    pokedex.pokemons = NULL;
    pokedex.qtd_pokemons = 0;
    pokedex.halt = false;

    do
    {
        leComandos(&pokedex);
    }while (!pokedex.halt);
    free(pokedex.pokemons);
    return 0;
}


void leComandos(Pokedex *pokedex){
    int comando;
    scanf("%d", &comando);
    switch (comando)
    {
    case 0:
        pokedex->halt = true;
        break;
    case 1:
        cadastroPokemon(pokedex);
        break;
    case 2:
        addAtaque(pokedex);
        break;
    case 3:
        imprimePokemon(pokedex);
        break;
    case 4:
        imprimeAtaque(pokedex);
        break;
    default:
        break;
    }
}


void cadastroPokemon(Pokedex *pokedex){
    Pokemon novoPokemon;
    pokedex->pokemons = realloc(pokedex->pokemons, (pokedex->qtd_pokemons+1) * sizeof(Pokemon));
    scanf(" %s", novoPokemon.nome);
    scanf(" %s", novoPokemon.primario);
    scanf(" %s", novoPokemon.secundario);
    scanf(" %d", &novoPokemon.atributos.hp);
    scanf(" %d", &novoPokemon.atributos.ataque);
    scanf(" %d", &novoPokemon.atributos.defesa);
    scanf(" %d", &novoPokemon.atributos.atk_especial);
    scanf(" %d", &novoPokemon.atributos.def_especial);
    scanf(" %d", &novoPokemon.atributos.velocidade);
    pokedex->pokemons[pokedex->qtd_pokemons++] = novoPokemon;
}

void addAtaque(Pokedex *pokedex){
    int indice_pokemon, indice_ataque;
    scanf(" %d", &indice_pokemon);
    scanf(" %d", &indice_ataque);
    scanf(" %s", pokedex->pokemons[indice_pokemon].ataques[indice_ataque].nome);
    scanf(" %d", &pokedex->pokemons[indice_pokemon].ataques[indice_ataque].poder_base);
    scanf(" %f", &pokedex->pokemons[indice_pokemon].ataques[indice_ataque].acuracia);
    scanf(" %c", &pokedex->pokemons[indice_pokemon].ataques[indice_ataque].classe);
}


void imprimePokemon(Pokedex *pokedex){
    int indice_pokemon;
    scanf(" %d", &indice_pokemon);
    printf("Nome do Pokemon: %s\n", pokedex->pokemons[indice_pokemon].nome);
    printf("Tipo primario: %s\n", pokedex->pokemons[indice_pokemon].primario);
    printf("Tipo secundario: %s\n", pokedex->pokemons[indice_pokemon].secundario);
    printf("Status:\n");
    printf("\tHP: %d\n", pokedex->pokemons[indice_pokemon].atributos.hp);
    printf("\tAtaque: %d\n", pokedex->pokemons[indice_pokemon].atributos.ataque);
    printf("\tDefesa: %d\n", pokedex->pokemons[indice_pokemon].atributos.defesa);
    printf("\tAtaque Especial: %d\n", pokedex->pokemons[indice_pokemon].atributos.atk_especial);
    printf("\tDefesa Especial: %d\n", pokedex->pokemons[indice_pokemon].atributos.def_especial);
    printf("\tVelocidade: %d\n\n", pokedex->pokemons[indice_pokemon].atributos.velocidade);
}

void imprimeAtaque(Pokedex *pokedex){
    int indice_pokemon, indice_ataque;
    scanf(" %d", &indice_pokemon);
    scanf(" %d", &indice_ataque);
    printf("Nome do Ataque: %s\n", pokedex->pokemons[indice_pokemon].ataques[indice_ataque].nome);
    printf("Poder base: %d\n", pokedex->pokemons[indice_pokemon].ataques[indice_ataque].poder_base);
    printf("Acuracia: %f\n", pokedex->pokemons[indice_pokemon].ataques[indice_ataque].acuracia);
    printf("Classe: %c\n\n", pokedex->pokemons[indice_pokemon].ataques[indice_ataque].classe);
}