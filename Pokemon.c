#include "Pokemon.h"
#include "Defs.h"

// Created by Noam Avizmil on 20/11/2025
/*
Initializer for pokemone structer below
*/
ResultStatus init_pokemon(Pokemone* pokemon, char* name, char* specie, char* type,float height, float weight, int attack){
  BioCreate(&pokemon->bio, height, weight, attack);
  pokemon->name = (char*)malloc(strlen(name) + 1);
  if (pokemon->name == NULL){return failure;}
  strcpy(pokemon->name, name);
  pokemon->specie = (char*)malloc(strlen(specie) + 1);
  if (pokemon->specie == NULL){free(pokemon->name);return failure;}
  strcpy(pokemon->specie, specie);
  pokemon->type = (char*)malloc(strlen(type) + 1);
  if (pokemon->type == NULL){free(pokemon->name);free(pokemon->specie);return failure;}
  strcpy(pokemon->type, type);
  return success;
}
void BioCreate(Bio_info *bio, float height, float weight, int attack){
  bio->attack = attack;
  bio->weight = weight;
  bio->height = height;

}
ResultStatus printBio(Bio_info* bio){
  printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", bio->height,bio->weight,bio->attack);
  return success;
}
ResultStatus PrintPokemon(Pokemone* pokemon){
  printf("%s :\n", pokemon->name);
  printf("%s, %s Type.\n", pokemon->specie,pokemon->type);
  ResultStatus x = printBio(&pokemon->bio);
  if (x == success){return success;}
  else{return failure;}
}
void delete_pokemon(Pokemone* pokemon){
free(pokemon->name);
free(pokemon->specie);
free(pokemon->type);

}
/*
the function below is initializing PokemonList with defining the name as for now
*/
ResultStatus init_pokemonList(PokemoneList* pokemonList, char* name){
  pokemonList->type_name = (char*)malloc(strlen(name) + 1);
  if (pokemonList->type_name == NULL){return failure;}
  strcpy(pokemonList->type_name, name);
  pokemonList->count_against_others = 0;
  pokemonList->count_against_me = 0;
  pokemonList->p_type_count =0;
  pokemonList->effective_against_me = NULL;
  pokemonList->effective_against_others = NULL;

  return success;
}
ResultStatus addEffectiveAgainstMe(PokemoneList* pokemonListA, PokemoneList* pokemonListB){
  if (pokemonListA->count_against_me == 0|| pokemonListA->effective_against_me == NULL){
    pokemonListA->effective_against_me =(PokemoneList**)malloc(sizeof(PokemoneList*));
    if (pokemonListA->effective_against_me == NULL){return failure;}
  }
  else{
    PokemoneList** temp = (PokemoneList**)realloc(pokemonListA->effective_against_me,(pokemonListA->count_against_me+1)*sizeof(PokemoneList*));
    if(temp == NULL){return failure;}
    pokemonListA->effective_against_me = temp;
  }
  pokemonListA->effective_against_me[pokemonListA->count_against_me] = pokemonListB;
  pokemonListA->count_against_me++;
  return success;
}
ResultStatus addEffectiveAgainstOthers(PokemoneList* pokemonListA, PokemoneList* pokemonListB){
  if (pokemonListA->count_against_others == 0|| pokemonListA->effective_against_others == NULL){
    pokemonListA->effective_against_others =(PokemoneList**)malloc(sizeof(PokemoneList*));
    if (pokemonListA->effective_against_others == NULL){return failure;}
  }
  else{
    PokemoneList** temp = (PokemoneList**)realloc(pokemonListA->effective_against_others,(pokemonListA->count_against_others+1)*sizeof(PokemoneList*));
    if(temp == NULL){return failure;}
    pokemonListA->effective_against_others = temp;
  }
  pokemonListA->effective_against_others[pokemonListA->count_against_others] = pokemonListB;
  pokemonListA->count_against_others++;
  return success;
}
ResultStatus DeleteAgainstMe(PokemoneList* pokemonListA, char* name){
  if (pokemonListA->count_against_me == 0 || pokemonListA->effective_against_me ==NULL ){return failure;}
  else{
    for (int i = 0; i < pokemonListA->count_against_me; i++){
      if(strcmp(pokemonListA->effective_against_me[i]->type_name, name) == 0){
        //after freeing we must move all -1 places for not storing garbage and collapsing
        for(int j = i; j < pokemonListA->count_against_me -1; j++){
           pokemonListA->effective_against_me[j] =pokemonListA->effective_against_me[j+1];
        }
        pokemonListA->count_against_me--;
        if(pokemonListA->count_against_me == 0){free(pokemonListA->effective_against_me); pokemonListA->effective_against_me = NULL;}
        else{
          PokemoneList** temp =(PokemoneList**)realloc(pokemonListA->effective_against_me,(pokemonListA->count_against_me)*sizeof(PokemoneList*));
          if(temp != NULL){
            pokemonListA->effective_against_me = temp;
          }
        }
        return success;
      }
    }
    return failure;
  }
}
ResultStatus DeleteAgainstOthers(PokemoneList* pokemonListA, char* name){
  if (pokemonListA->count_against_others == 0|| pokemonListA-> effective_against_others == NULL){return failure;}
  else{
    for (int i = 0; i < pokemonListA->count_against_others; i++){
      if(strcmp(pokemonListA->effective_against_others[i]->type_name, name) == 0){

        for(int j = i; j < pokemonListA->count_against_others -1; j++){
          pokemonListA->effective_against_others[j] =pokemonListA->effective_against_others[j+1];
        }
        pokemonListA->count_against_others--;
        if(pokemonListA->count_against_others == 0){free(pokemonListA->effective_against_others);pokemonListA->effective_against_others = NULL;}
        else{
          PokemoneList** temp =(PokemoneList**)realloc(pokemonListA->effective_against_others,(pokemonListA->count_against_others)*sizeof(PokemoneList*));
          if(temp != NULL){
            pokemonListA->effective_against_others = temp;
          }
        }
        return success;
      }
    }
    return failure;
  }
}
ResultStatus DeleteList(PokemoneList* pokemonList){
  if(pokemonList-> effective_against_me != NULL){
    free(pokemonList->effective_against_me);
    pokemonList->effective_against_me = NULL;
  }
  if(pokemonList-> effective_against_others != NULL){
    free(pokemonList->effective_against_others);
  pokemonList->effective_against_others = NULL;
  }
  if(pokemonList->type_name != NULL){
  free(pokemonList->type_name);
  pokemonList->type_name = NULL;
  }
  return success;
}
ResultStatus PrintPokemonList(PokemoneList* pokemonList){
      printf("Type %s -- %d pokemons\n",pokemonList->type_name,pokemonList->p_type_count);
	  //if (pokemonList->p_type_count == 0){ResultStatus x = DeleteList(pokemonList); return x;}
      if(pokemonList->count_against_me != 0){
        printf("\tThese types are super-effective against %s:",pokemonList->type_name);
        for(int i = 0; i < pokemonList->count_against_me; i++){
          printf("%s", pokemonList->effective_against_me[i]->type_name);
          if (i != pokemonList->count_against_me - 1){
            printf(" ,");
          }
        }
        printf("\n");
      }
      if (pokemonList->count_against_others != 0){
        printf("\n\t%s moves are super-effective against:",pokemonList->type_name);
        for(int i = 0; i < pokemonList->count_against_others; i++){
             printf("%s", pokemonList->effective_against_others[i]->type_name);
             if (i != pokemonList->count_against_others - 1){
                printf(" ,");
             }
        }
        printf("\n");
      }
      if (pokemonList->count_against_me != 0&&pokemonList->count_against_others != 0){printf("\n");}
      else{printf("\n\n");}

      return success;
}
