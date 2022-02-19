// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021

#include <string.h>
#include "Pokemon.h"

// The function indicates if the memory allocated correctly:         //
// True     : if one of the pointers is NULL.                        //
// False    : if all the pointers have a valid value.                //
// ---number of parameters should be passed as the first argument--- //


// Initialization of biological data "instance"                     //
// The function returns a pointer to BData variable.                //
BData *Create_Biological_Data(float height, float weight, int attack) {
    // Memory allocation for BData variable:
    BData *biological_data = (BData *) malloc(sizeof(BData));
    if (biological_data == NULL) {                             // Proper allocation check.
        return NULL;
    }
    biological_data->height =0;
    biological_data->weight =0;
    biological_data->attack =0;

    biological_data->height = height;
    biological_data->weight = weight;
    biological_data->attack = attack;
    return biological_data;
}

// Initialization of Pokemon type "instance"                        //
// The function returns a pointer to Pokemon type variable.         //

PType *Create_Pokemon_Type(char *type_name) {
    if (type_name == NULL) {
        return NULL;
    }; // Proper allocation check
    PType *pokemon_type = (PType *) malloc(sizeof(PType));
    if (pokemon_type == NULL) {
        return NULL;
    }
    pokemon_type->type_name = (char *) malloc(sizeof(char) * strlen(type_name) + 1);
    if (pokemon_type->type_name == NULL) {
        free(pokemon_type);
        return NULL;
    }

    strcpy(pokemon_type->type_name, type_name);
    pokemon_type->effective_against_me = NULL;                        // Double pointing (!)
    pokemon_type->effective_against_others = NULL;                    // Double pointing (!)
    pokemon_type->HowManyFromType = 0;
    pokemon_type->HowManyMe = 0;
    pokemon_type->HowManyOther = 0;
    pokemon_type->pPokemon = NULL;
    return pokemon_type;
}

// Deleting Pokemon type "instance"                                 //
// The function returns void (nothing)                              //
void deleteType(PType *Type) {
    if (Type == NULL) {
        return;
    }
    free(Type->type_name);
    Type->type_name = NULL;
    free(Type->pPokemon);
    Type->pPokemon = NULL;
    free(Type);
    Type = NULL;
}

// Deleting Pokemon type effective lists (me/others)                //
// The function returns void (nothing)                              //
void deleteEffectiveness(PType *type) {
    if (type == NULL) {
        return;
    }
    free(type->effective_against_me);
    free(type->effective_against_others);
}

// Initialization of Pokemon "instance"                             //
// The function returns a pointer to Pokemon variable.              //
Pokemon *Create_Pokemon(char *name, char *species, float height, float weight, int attack, PType *pokemon_type) {
    if (name == NULL || species == NULL || pokemon_type == NULL) {
        return NULL;
    }
    Pokemon *pokemon = (Pokemon *) malloc(sizeof(Pokemon));
    if (pokemon == NULL) {
        return NULL;
    }
    pokemon->name = (char *) malloc(sizeof(char) * (strlen(name)) + 1);
    if (pokemon->name == NULL) {
        free(pokemon);
        return NULL;
    }
    strcpy(pokemon->name, name);
    pokemon->species = (char *) malloc(sizeof(char) * (strlen(species)) + 1);
    if (pokemon->species == NULL) {
        free(pokemon->name);
        free(pokemon);
        return NULL;
    }
    strcpy(pokemon->species, species);
    BData *bData = Create_Biological_Data(height, weight, attack);
    if (bData == NULL) {
        free(pokemon->name);
        free(pokemon->species);
        free(pokemon);
        return NULL;
    }

    pokemon->data = bData;
    pokemon->type = pokemon_type;
    return pokemon;
}

// Deleting Pokemon "instance"                                      //
// The function returns void (nothing)                              //
void deletePokemon(Pokemon *pokemon) {
    if (pokemon == NULL) {
        return;
    }
    deleteBD(pokemon->data);
    pokemon->data = NULL;
    pokemon->type = NULL;
    free(pokemon->name);
    pokemon->name = NULL;
    free(pokemon->species);
    pokemon->species = NULL;
    free(pokemon);
    pokemon = NULL;
}

// Deleting Pokemon biological information                          //
// The function returns void (nothing)                              //
void deleteBD(BData *biological_data) {
    if (biological_data == NULL) {
        return;
    }
    free(biological_data);
    biological_data = NULL;
}

// Printing Pokemon by format                                       //
// The function returns void (nothing)                              //
status PokemonToString(Pokemon *pokemon) {
    if (pokemon == NULL) {
        return failure; // Memory Problem, failure status -> safeExit.
    }
    printf("%s :\n", pokemon->name);
    printf("%s, %s Type.\n", pokemon->species, pokemon->type->type_name);
    printf("Height: %.2f m    Weight: %.2f kg    Attack: %d", pokemon->data->height, pokemon->data->weight,
           pokemon->data->attack);
    printf("\n\n");
    return success;
}

// Printing Pokemon type by format                                  //
// The function returns void (nothing)                              //
status TypeToString(PType *type) {
    if (type == NULL) {
        return failure; // Memory Problem, failure status -> safeExit.
    }
    printf("Type %s -- %d pokemons\n", type->type_name, type->HowManyFromType);
    if (type->HowManyMe != 0) {
        printf("\tThese types are super-effective against %s:", type->type_name);
        for (int i = 0; i < type->HowManyMe; ++i) {
            if (i == type->HowManyMe - 1) {
                printf("%s\n", type->effective_against_me[i]->type_name);
            } else {
                printf("%s ,", type->effective_against_me[i]->type_name);
            }
        }
    }
    if (type->HowManyOther != 0) {
        printf("\t%s moves are super-effective against:", type->type_name);
        for (int i = 0; i < type->HowManyOther; ++i) {
            if (i == type->HowManyOther - 1) {
                printf("%s", type->effective_against_others[i]->type_name);
            } else {
                printf("%s ,", type->effective_against_others[i]->type_name);
            }
        }
    }
    if (type->HowManyOther == 0) {
        printf("\n");
    } else {
        printf("\n\n");
    }
    return success;
}

// Check if a given type is exist.                                  //
// The function gets the type by name,                              //
// and returns pointer to it if exist                               //
PType *getTypeIfExist(char *name, PType **types, int numberOfTypes) {
    if (name == NULL || types == NULL) {
        return NULL;
    }
    for (int i = 0; i < numberOfTypes; ++i) {
        if (strcmp(name, types[i]->type_name) == 0)
            return types[i];
    }
    return NULL;
}

// Check if a given Pokemon exists.                                 //
// The function gets the Pokemon by name,                           //
// and returns pointer to it if exist                               //
Pokemon *getPokemonIfExist(char *name, Pokemon **pokemons, int numberOfPokemons) {
    if (name == NULL || pokemons == NULL) {
        return NULL;
    }
    for (int i = 0; i < numberOfPokemons; ++i) {
        if (strcmp(name, pokemons[i]->name) == 0)
            return pokemons[i];
    }
    return NULL;
}


// Function inserting target type into source types                  //
// "effective against me" list - as described in case (3) comment.   //
status
Insert_into_effective_against_me(char *insert_into_this_types_list, char *the_type_to_add, PType **typeList, int n) {
    if (insert_into_this_types_list == NULL || the_type_to_add == NULL || typeList == NULL) {
        return failure;
    }
    PType *sourceType = getTypeIfExist(insert_into_this_types_list, typeList, n);
    PType *targetType = getTypeIfExist(the_type_to_add, typeList, n);
    if (sourceType->effective_against_me == NULL) {
        sourceType->effective_against_me = (PType **) malloc(sizeof(PType *));
        if (sourceType->effective_against_me == NULL) {
            return failure;
        }
        sourceType->effective_against_me[0] = targetType;
        sourceType->HowManyMe++;
    } else {
        sourceType->HowManyMe++;
        sourceType->effective_against_me = (PType **) realloc(sourceType->effective_against_me,
                                                              (sizeof(PType *) * (sourceType->HowManyMe)) + 1);
        if (sourceType->effective_against_me == NULL) {
            return failure;
        }
        sourceType->effective_against_me[sourceType->HowManyMe - 1] = targetType;
    }
    return success;
}

// Function inserting target type into source types                  //
// "effective against other" list - as described in case (4)         //
status Insert_into_effective_against_others(char *insert_into_this_types_list, char *the_type_to_add, PType **typeList,
                                            int n) {
    if (insert_into_this_types_list == NULL || the_type_to_add == NULL || typeList == NULL) {
        return failure;
    }
    PType *sourceType = getTypeIfExist(insert_into_this_types_list, typeList, n);
    PType *targetType = getTypeIfExist(the_type_to_add, typeList, n);
    if (sourceType->effective_against_others == NULL) {
        sourceType->effective_against_others = (PType **) malloc(sizeof(PType *));
        if (sourceType->effective_against_others == NULL) {
            return failure;
        }
        sourceType->effective_against_others[0] = targetType;
        sourceType->HowManyOther++;
    } else {
        sourceType->HowManyOther++;
        sourceType->effective_against_others = (PType **) realloc(sourceType->effective_against_others,
                                                                  sizeof(PType *) * (sourceType->HowManyOther));
        if (sourceType->effective_against_others == NULL) {
            return failure;
        }
        sourceType->effective_against_others[sourceType->HowManyOther - 1] = targetType;
    }
    return success;
}

// Function removing target type from source types                   //
// "effective against me" list - as described in case (5) comment.   //
status Delete_type_from_effective_against_me_list(PType *delete_from_this_type_list, PType *delete_this_type) {
    if (delete_from_this_type_list == NULL || delete_this_type == NULL) {
        return failure;
    }
    int counter = 0;
    PType *temp[delete_from_this_type_list->HowManyMe];
    for (int i = 0; i < delete_from_this_type_list->HowManyMe; ++i) {
        if (strcmp(delete_from_this_type_list->effective_against_me[i]->type_name, delete_this_type->type_name) != 0) {
            temp[counter] = delete_from_this_type_list->effective_against_me[i];
            counter++;
        }
    }
    delete_from_this_type_list->effective_against_me = (PType **) realloc(
            delete_from_this_type_list->effective_against_me,
            sizeof(PType *) * (delete_from_this_type_list->HowManyMe));
    if (delete_from_this_type_list->effective_against_me == NULL) {
        return failure;
    }
    for (int i = 0; i < delete_from_this_type_list->HowManyMe - 1; ++i) {
        delete_from_this_type_list->effective_against_me[i] = temp[i];
    }
    delete_from_this_type_list->HowManyMe--;
    return success;
}

// Function removing target type from source types                      //
// "effective against other" list - as described in case (6) comment.   //
status Delete_type_from_effective_against_others_list(PType *delete_from_this_type_list, PType *delete_this_type) {
    if (delete_from_this_type_list == NULL || delete_this_type == NULL) {
        return failure;
    }
    PType *temp[delete_from_this_type_list->HowManyOther];
    int counter = 0;
    for (int i = 0; i < delete_from_this_type_list->HowManyOther; ++i) {
        if (strcmp(delete_from_this_type_list->effective_against_others[i]->type_name, delete_this_type->type_name) !=
            0) {
            temp[counter] = delete_from_this_type_list->effective_against_others[i];
            counter++;
        }
    }
    delete_from_this_type_list->effective_against_others = (PType **) realloc(
            delete_from_this_type_list->effective_against_others,
            sizeof(PType *) * (delete_from_this_type_list->HowManyOther));
    if (delete_from_this_type_list->effective_against_others == NULL) {
        return failure;
    }
    for (int i = 0; i < delete_from_this_type_list->HowManyOther - 1; ++i) {
        delete_from_this_type_list->effective_against_others[i] = temp[i];
    }
    delete_from_this_type_list->HowManyOther--;
    return success;
}

// function to insert pokemon into the "Main" Pokemons list,    //
// I called that list "pPokemons_list" in the FirstMain.c code. //
void InsertPokemonIntoPokemonListInsideType(PType *type, Pokemon *pokemon) {
    if (type == NULL || pokemon == NULL) {
        return;
    }
    if (type->pPokemon == NULL) {
        type->pPokemon = (Pokemon **) malloc(sizeof(Pokemon *));
        if (type->pPokemon == NULL) {
            return;
        }
        type->pPokemon[0] = pokemon;
    } else {
        type->pPokemon = (Pokemon **) realloc(type->pPokemon, sizeof(Pokemon *) * type->HowManyFromType);
        if (type->pPokemon == NULL) {
            return;
        }
        type->pPokemon[type->HowManyFromType - 1] = pokemon;
    }
}

int isEqualPokemon(Pokemon *pokemon1, Pokemon *pokemon2) {
    if (pokemon1 == NULL || pokemon2 == NULL){
        return -2;
    }

    if (pokemon1->data->attack > pokemon2->data->attack) {
        return 1;
    } else if (pokemon2->data->attack > pokemon1->data->attack) {
        return -1;
    } else
        return 0;
}

Pokemon *copyPokemon(Pokemon *pokemon) {
//    Pokemon *new = (Pokemon *) malloc(sizeof(Pokemon));
//    new->name = (char *) malloc(sizeof(char) * strlen(pokemon->name));
//    new->species = (char *) malloc(sizeof(char) * strlen(pokemon->species));
//    strcpy(new->name, pokemon->name);
//    strcpy(new->species, pokemon->species);
//    new->data = Create_Biological_Data(pokemon->data->height, pokemon->data->weight, pokemon->data->attack);
//    new->type = pokemon->type;
//    return new;

    return pokemon;
}

char *getTypeName(Pokemon *pokemon) {
    return pokemon->type->type_name;
}

int getAttack(Pokemon *pokemon1, Pokemon *pokemon2, int *attack1, int *attack2) {
    bool reducedFromFirst = false;
    bool reducedFromSecond = false;
    int first_attack = pokemon1->data->attack;
    int second_attack = pokemon2->data->attack;
    for (int i = 0; i < pokemon1->type->HowManyMe; ++i) {
        if (pokemon1->type->effective_against_me[i] == pokemon2->type && reducedFromFirst == false) {
            first_attack -= 10;
            reducedFromFirst = true;
        }
    }
    for (int i = 0; i < pokemon1->type->HowManyOther; ++i) {
        if (pokemon1->type->effective_against_others[i] == pokemon2->type && reducedFromSecond == false) {
            second_attack -= 10;
            reducedFromSecond = true;
        }
    }
    for (int i = 0; i < pokemon2->type->HowManyMe; ++i) {
        if (pokemon2->type->effective_against_me[i] == pokemon1->type && reducedFromSecond == false) {
            second_attack -= 10;
            reducedFromSecond = true;
        }
    }
    for (int i = 0; i < pokemon2->type->HowManyOther; ++i) {
        if (pokemon2->type->effective_against_others[i] == pokemon1->type && reducedFromFirst == false) {
            first_attack -= 10;
            reducedFromFirst = true;
        }
    }
    *attack1 = first_attack;
    *attack2 = second_attack;
    return (first_attack-second_attack);
}