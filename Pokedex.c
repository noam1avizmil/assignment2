//
// Created by Noam Avizmil on 20/11/2025.
//
#include "Pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
int find_type_index(PokemoneList* types, int count, char* type) {
    for (int i = 0; i < count; i++) {
        if (strcmp(types[i].type_name, type) == 0) {return i;}
    }
    return -1;
}

ResultStatus main(int argc, char* argv[]) {
    int numberofTypes = atoi(argv[1]);
    int numberofPokemons = atoi(argv[2]);
    FILE * config_file = fopen(argv[3], "r");
    if (config_file == NULL){return failure;}
    char buffer[300];
    fgets(buffer, sizeof(buffer), config_file);
    PokemoneList* types = (PokemoneList*)malloc(numberofTypes*sizeof(PokemoneList));
    Pokemone* pokemons = (Pokemone*)malloc(numberofPokemons*sizeof(Pokemone));
    fgets(buffer,sizeof(buffer), config_file);
    char* curr_type = strtok(buffer,",\n"); //array of types
    int curr = 0;
    while(curr_type != NULL && curr < numberofTypes){
    init_pokemonList(&types[curr],curr_type);
    curr++;
    curr_type = strtok(NULL,",\n");//null to go from where we left.
    }
    while(fgets(buffer,sizeof(buffer),config_file) != NULL) {
        if (strstr(buffer, "Pokemons")){break;}
        if (strstr(buffer, "effective-against-me:")) {
            char* source = strtok(buffer," ");
            strtok(NULL,":");
            char* effective_against_me = strtok(NULL,"\n");
            int s_idx = find_type_index(types, numberofTypes, source);
            char* effective_against_me_i = strtok(effective_against_me,",");
            while (effective_against_me_i != NULL) {
                int e_idx = find_type_index(types, numberofTypes, effective_against_me_i);
                addEffectiveAgainstMe(&types[s_idx], &types[e_idx]);
                effective_against_me_i = strtok(NULL,",");
            }
        }
    }






}
