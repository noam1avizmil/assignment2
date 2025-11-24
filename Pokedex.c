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
        else if (strstr(buffer, "effective-against-others:")) {
            char* source = strtok(buffer," ");
            strtok(NULL,":");
            char* effective_against_others = strtok(NULL,"\n");
            int s_idx = find_type_index(types, numberofTypes, source);
            char* effective_against_others_i = strtok(effective_against_others,",");
            while (effective_against_others_i != NULL) {
                int e_idx = find_type_index(types, numberofTypes, effective_against_others_i);
                addEffectiveAgainstOthers(&types[s_idx], &types[e_idx]);
                effective_against_others_i = strtok(NULL,",");
            }
        }
    }
    int p_idx = 0;
    while (fgets(buffer,sizeof(buffer),config_file) != NULL && p_idx < numberofPokemons) {
        char* name = strtok(buffer,",");
        char* specie = strtok(NULL,",");
        float height = atof(strtok(NULL,","));
        float weight = atof(strtok(NULL, ","));
        int attack = atoi(strtok(NULL, ","));
        char* type = strtok(NULL, ",\n");
        init_pokemon(&pokemons[p_idx],name,specie,type,height,weight,attack);
        int t_idx = find_type_index(types, numberofTypes, type);
        if (t_idx >= 0){types[t_idx].p_type_count++;}
        p_idx++;
    }
    fclose(config_file);








}
