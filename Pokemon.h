//
// Created by Noam Avizmil on 20/11/2025.
//
#ifndef ASSIG2_POKEMON_H
#define ASSIG2_POKEMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

/*
struct creation
*/
typedef struct {
  float height;
  float weight;
  int attack;
} Bio_info;

typedef struct {
  Bio_info bio;
  char* name;
  char* specie;
  char* type;
} Pokemone;
typedef struct type {
  char* type_name;
  struct type** effective_against_others;
  struct type** effective_against_me;
  int count_against_others ;
  int count_against_me ;
  int p_type_count;

} PokemoneList;

ResultStatus init_pokemon(Pokemone* pokemon, char* name, char* specie, char* type,float height, float weight, int attack);
ResultStatus PrintPokemon(Pokemone* pokemon);
void delete_pokemon(Pokemone* pokemon);
ResultStatus init_pokemonList(PokemoneList* pokemonList, char* name);
ResultStatus addEffectiveAgainstMe(PokemoneList* pokemonListA, PokemoneList* pokemonListB);
ResultStatus addEffectiveAgainstOthers(PokemoneList* pokemonListA, PokemoneList* pokemonListB);
ResultStatus DeleteAgainstMe(PokemoneList* pokemonListA, char* name);
ResultStatus DeleteAgainstOthers(PokemoneList* pokemonListA, char* name);
ResultStatus printBio(Bio_info* bio);
ResultStatus DeleteList(PokemoneList* pokemonList);
ResultStatus PrintPokemonList(PokemoneList* pokemonList);
void BioCreate(Bio_info *bio, float height, float weight, int attack);
#endif //ASSIG2_POKEMON_H