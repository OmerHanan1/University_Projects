//
// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021
//

#ifndef C_PROJECT_POKEMON_H
#define C_PROJECT_POKEMON_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Defs.h"

// struct of biological information:
typedef struct Biological_Data_t{
    float height;                              // Pokemon's height
    float weight;                              // Pokemon's weight
    int attack;                                 // Pokemon's attack value
} BData;

// struct of pokemon type
typedef struct Pokemon_Type_t{
    char *type_name;                                   // Type name
    struct Pokemon_Type_t **effective_against_me;      // Array of "effective against me" types
    struct Pokemon_Type_t **effective_against_others;  // Array of "effective against others" types
    int HowManyFromType;
    int HowManyMe;
    int HowManyOther;
    struct Pokemon_t **pPokemon;
} PType;

// struct of pokemon
typedef struct Pokemon_t{
    char *name;                                 // Pokemon name
    char *species;                              // Pokemon species
    BData *data;                                // Biological data
    PType *type;                                // Pokemon type
} Pokemon;

// Functions
Pokemon *Create_Pokemon(char *name, char *species, float height, float weight, int attack, PType *pokemon_type);
PType *Create_Pokemon_Type(char *type_name);
Pokemon *getPokemonIfExist(char *name, Pokemon **pokemons, int numberOfPokemons);
PType *getTypeIfExist(char *name, PType **types, int numberOfTypes);
status TypeToString(PType *);
status PokemonToString(Pokemon *pokemon);
status Delete_type_from_effective_against_me_list(PType *delete_from_this_type_list, PType *delete_this_type);
status Delete_type_from_effective_against_others_list(PType *delete_from_this_type_list, PType *delete_this_type);
void deleteType(PType *Type);
void deleteEffectiveness(PType *type);
void deleteBD(BData *biological_data);
void deletePokemon(Pokemon *pokemon);
status Insert_into_effective_against_me(char *insert_into_this_types_list, char *the_type_to_add, PType **typeList, int n);
status Insert_into_effective_against_others(char *insert_into_this_types_list, char *the_type_to_add, PType **typeList, int n);
void InsertPokemonIntoPokemonListInsideType(PType *type, Pokemon *pokemon);

#endif //C_PROJECT_POKEMON_H
