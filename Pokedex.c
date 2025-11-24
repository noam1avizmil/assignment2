//
// Created by Noam Avizmil on 20/11/2025.
//
#include "Pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#iclude "Defs.h""

ResultStatus main(int argc, char* argv[]) {
    numberofTypes = atoi(argv[1];)
    numberofPokemons = atoi(argv[2];)
    File config_file = fopen(argv[3], "r");
    if (config_file == NULL){return failure;}
    char buffer[300];
    fgets(buffer, sizeof(buffer), config_file);
    PokemonList* types = (pokemonList*)malloc(numberofTypes*sizeof(pokemonList));
    Pokemone* pokemons = (Pokemone*)malloc(numberofPokemons*sizeof(Pokemone));
    fgets(buffer,sizeof(buffer), config_file);
    char* curr_type = strtok(buffer,",\n"); //array of types
    int curr = 0;
    while(curr_type != NULL && curr < numberofTypes){
    init_pokemonList(&types[curr],curr_type);
    curr++;
    curr_type = strtok(NULL,",\n");//null to go from where we left.
    }







}
