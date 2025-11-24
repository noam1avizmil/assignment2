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

int main(int argc, char* argv[]) {
    const char* DELIMS = " \t\r\n,";
    int numberofTypes = atoi(argv[1]);
    int numberofPokemons = atoi(argv[2]);
    FILE * config_file = fopen(argv[3], "r");
    if (config_file == NULL){return 1;}
    char buffer[300];
    fgets(buffer, sizeof(buffer), config_file);
    PokemoneList* types = (PokemoneList*)malloc(numberofTypes*sizeof(PokemoneList));
    if (types == NULL){fclose(config_file);return 1;}
    Pokemone* pokemons = (Pokemone*)malloc(numberofPokemons*sizeof(Pokemone));
    if (pokemons == NULL) {
        printf("Memory Problem\n");
        free(types);
        fclose(config_file);
        return 1;
    }
    fgets(buffer,sizeof(buffer), config_file);
    char* curr_type = strtok(buffer,DELIMS);
    int curr = 0;
    while(curr_type != NULL && curr < numberofTypes){
        init_pokemonList(&types[curr],curr_type);
        curr++;
        curr_type = strtok(NULL,DELIMS);
    }
    while(fgets(buffer,sizeof(buffer),config_file) != NULL) {
        if (strstr(buffer, "Pokemons")){break;}
        if (strstr(buffer, "effective-against-me:")) {
            char* source = strtok(buffer,DELIMS);
            strtok(NULL,":");
            int s_idx = find_type_index(types, numberofTypes, source);
            char* effective_against_me_i = strtok(NULL,DELIMS);
            while (effective_against_me_i != NULL) {
                int e_idx = find_type_index(types, numberofTypes, effective_against_me_i);
                if (s_idx != -1 && e_idx != -1) {
                    addEffectiveAgainstMe(&types[s_idx], &types[e_idx]);
                }
                effective_against_me_i = strtok(NULL,DELIMS);
            }
        }
        else if (strstr(buffer, "effective-against-other:")) {
            char* source = strtok(buffer,DELIMS);
            strtok(NULL,":");
            int s_idx = find_type_index(types, numberofTypes, source);
            char* effective_against_others_i = strtok(NULL,DELIMS);
            while (effective_against_others_i != NULL) {
                int e_idx = find_type_index(types, numberofTypes, effective_against_others_i);
                if (s_idx != -1 && e_idx != -1) {
                    addEffectiveAgainstOthers(&types[s_idx], &types[e_idx]);
                }
                effective_against_others_i = strtok(NULL,DELIMS);
            }
        }
    }
    int p_idx = 0;
    while (fgets(buffer,sizeof(buffer),config_file) != NULL && p_idx < numberofPokemons) {
        char* name = strtok(buffer,DELIMS);
        char* specie = strtok(NULL,DELIMS);
        float height = atof(strtok(NULL,DELIMS));
        float weight = atof(strtok(NULL,DELIMS));
        int attack = atoi(strtok(NULL,DELIMS));
        char* type = strtok(NULL,DELIMS);
        init_pokemon(&pokemons[p_idx],name,specie,type,height,weight,attack);
        int t_idx = find_type_index(types, numberofTypes, type);
        if (t_idx >= 0){types[t_idx].p_type_count++;}
        p_idx++;
    }
    fclose(config_file);
    //menu
    int c = 0;
    int ch;
    char word[300];
    while (c!=9) {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons\n2 : Print all Pokemons types\n3 : Add type to effective against me list\n4 : Add type to effective against others list\n");
        printf("5 : Remove type from effective against me list\n6 : Remove type from effective against others list\n7 : Print Pokemon by name\n8 : Print Pokemons by type\n");
        printf("9 : Exit\n");
        if (scanf("%d",&c)!= 1 || c<1||c>9) {
            if (feof(stdin)) break;
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Please choose a valid number.\n");
            continue;
        }
        while ((ch = getchar()) != '\n' && ch != EOF);
        if (c==9) {

            break;
        }
        if (c==1) {
            for (int i = 0; i < numberofPokemons; i++) {
                PrintPokemon(&pokemons[i]);
            }
        }
        if (c==2) {
            for (int i = 0; i < numberofTypes; i++) {
                PrintPokemonList(&types[i]);
            }
        }
        if (c==3) {
            printf("Please enter type name:\n");
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int idx = find_type_index(types, numberofTypes, word);
            if (idx == -1){printf("Type name doesn't exist.\n");continue;}
            printf("Please enter type name to add to %s effective against me list:\n", word);
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int add_idx = find_type_index(types, numberofTypes, word);
            if (add_idx == -1){printf("Type name doesn't exist.\n");continue;}
            bool is_exist = 0;
            for (int i = 0; i < types[idx].count_against_me; i++) {
                if (strcmp(types[idx].effective_against_me[i]->type_name, word)== 0) {is_exist = 1;break;}
            }
            if (is_exist ==1) {printf("This type already exist in the list.\n");continue;}
            addEffectiveAgainstMe(&types[idx], &types[add_idx]);
            PrintPokemonList(&types[idx]);
        }
        if (c==4) {
            printf("Please enter type name:\n");
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int idx = find_type_index(types, numberofTypes, word);
            if (idx == -1){printf("Type name doesn't exist.\n");continue;}
            printf("Please enter type name to add to %s effective against others list:\n", word);
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int add_idx = find_type_index(types, numberofTypes, word);
            if (add_idx == -1){printf("Type name doesn't exist.\n");continue;}
            bool is_exist = false;
            for (int i = 0; i < types[idx].count_against_others; i++) {
                if (strcmp(types[idx].effective_against_others[i]->type_name, word)== 0) {is_exist = true ;break;}
            }
            if (is_exist == true) {printf("This type already exist in the list.\n");continue;}
            addEffectiveAgainstOthers(&types[idx], &types[add_idx]);
            PrintPokemonList(&types[idx]);
        }
        if (c==5) {
            printf("Please enter type name:\n");
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int idx = find_type_index(types, numberofTypes, word);
            if (idx == -1){printf("Type name doesn't exist.\n");continue;}
            printf("Please enter type name to remove from %s effective against me list:\n", word);
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            ResultStatus result =DeleteAgainstMe(&types[idx], word);
            if (result == failure){printf("Type name doesn't exist in the list.\n");}
            else{PrintPokemonList(&types[idx]);}
        }
        if (c==6) {
            printf("Please enter type name:\n");
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int idx = find_type_index(types, numberofTypes, word);
            if (idx == -1){printf("Type name doesn't exist.\n");continue;}
            printf("Please enter type name to remove from %s effective against others list:\n", word);
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            ResultStatus result =DeleteAgainstOthers(&types[idx], word);
            if (result == failure){printf("Type name doesn't exist in the list.\n");}
            else{PrintPokemonList(&types[idx]);}
        }
        if (c==7) {
            printf("Please enter Pokemon name:\n");
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            bool is_found = false;
            for (int i = 0; i < numberofPokemons; i++) {
                if (strcmp(pokemons[i].name,word)==0) {
                    is_found = true;
                    PrintPokemon(&pokemons[i]);
                    break;
                }
            }
            if (is_found == false){printf("The Pokemon doesn't exist.\n");}
        }
        if (c==8) {
            printf("Please enter type name:\n");
            scanf("%s",word);
            while ((ch = getchar()) != '\n' && ch != EOF);
            int idx = find_type_index(types, numberofTypes, word);
            if (idx == -1){printf("Type name doesn't exist.\n");continue;}
            int counter = 0;
            for (int i = 0; i < numberofPokemons; i++) {
                if (strcmp(pokemons[i].type, word)==0) {counter++;}
            }
            if (counter ==0){printf("There are no Pokemons with this type.\n");}
            else {
                printf("There are %d Pokemons with this type:\n", counter);
                for (int i = 0; i < numberofPokemons; i++) {
                    if (strcmp(pokemons[i].type, word)==0) {
                        PrintPokemon(&pokemons[i]);
                    }
                }
            }

        }
    }
    printf("All the memory cleaned and the program is safely closed.\n");
    for (int i = 0; i < numberofPokemons; i++) {
        delete_pokemon(&pokemons[i]);
    }
    for (int i = 0; i < numberofTypes; i++) {
        DeleteList(&types[i]);
    }
    free(types);
    free(pokemons);
    return 0;
}