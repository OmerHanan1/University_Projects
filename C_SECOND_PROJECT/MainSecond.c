#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Pokemon.h"
#include "BattleByCategory.h"
#include "Defs.h"

void safeExit(Battle battle, PType **pPTypes_list, int numberOfTypes);

Battle Pokedex_builder(int numberOfTypes, int CapacityOfType, int *total_num_of_pokemons, PType **pPTypes_list,
                       char *configurationTextFile);


int main(int argc, char *argv[]) {

    int numberOfTypes = atoi(argv[1]);
    int capacityInType = atoi(argv[2]);
    char *config = argv[3];
    int counter_how_many_pokemons_in_battle = 0;

    PType **Types = NULL;
    Types = (PType **) malloc(sizeof(PType *) * numberOfTypes);
    if (Types == NULL) {
        printf("No memory available.\n");
        return 1;
    }
    Battle b = Pokedex_builder(numberOfTypes, capacityInType, &counter_how_many_pokemons_in_battle, Types, config);
    if (b == NULL){
        printf("No memory available.\n");
        safeExit(b, Types, numberOfTypes);
        return 1;
    }

    bool flag = true;
    while (flag) {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons by types\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Insert Pokemon to battles training camp\n");
        printf("4 : Remove strongest Pokemon by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");

        char c[Buffer];
        scanf("%s", c);
        if (strlen(c) != 1) c[0] = 0;
        switch (c[0]) {

            case '1':
                displayObjectsByCategories(b);
                break;
            case '2':
                for (int i = 0; i < numberOfTypes; ++i) {
                    TypeToString(Types[i]);
                }
                break;
            case '3':
                printf("Please enter Pokemon type name:\n");
                char type[Buffer];
                scanf("%s", type);
                PType *temp = getTypeIfExist(type, Types, numberOfTypes);
                if (temp == NULL) {
                    printf("Type name doesn't exist.\n");
                    break;
                }
                if (getNumberOfObjectsInCategory(b, type) == capacityInType) {
                    printf("Type at full capacity.\n");
                    break;
                }
                printf("Please enter Pokemon name:\n");
                char name[Buffer];
                scanf("%s", name);
                printf("Please enter Pokemon species:\n");
                char species[Buffer];
                scanf("%s", species);
                printf("Please enter Pokemon height:\n");
                float height;
                scanf("%f", &height);
                printf("Please enter Pokemon weight:\n");
                float weight;
                scanf("%f", &weight);
                printf("Please enter Pokemon attack:\n");
                int attack;
                scanf("%d", &attack);

                Pokemon *new = Create_Pokemon(name, species, height, weight, attack, temp);
                if (new == NULL){
                    printf("No memory available.\n");
                    safeExit(b, Types, numberOfTypes);
                }
                if (insertObject(b, new) != failure) {
                    printf("The Pokemon was successfully added.\n");
                    for (int j = 0; j < numberOfTypes; ++j) {
                        if (strcmp(Types[j]->type_name, type) == 0) {
                            Types[j]->HowManyFromType++;
                            counter_how_many_pokemons_in_battle++;
                        }
                    }
                    PokemonToString(new);
                }
                else{
                    deletePokemon(new);
                }


                break;
            case '4':
                printf("Please enter type name:\n");
                char type_to_remove[Buffer];
                scanf("%s", type_to_remove);
                PType *temp_type_to_remove_from = getTypeIfExist(type_to_remove, Types, numberOfTypes);
                if (temp_type_to_remove_from != NULL) {
                    if (temp_type_to_remove_from->HowManyFromType == 0) {
                        printf("There is no Pokemon to remove.\n");
                        break;
                    }
                    printf("The strongest Pokemon was removed:\n");
                    Pokemon *remove = removeMaxByCategory(b, type_to_remove);
                    PokemonToString(remove);
                    for (int j = 0; j < numberOfTypes; ++j) {
                        if (strcmp(Types[j]->type_name, type_to_remove) == 0) {
                            Types[j]->HowManyFromType--;
                            counter_how_many_pokemons_in_battle--;
                        }
                    }
                    deletePokemon(remove);
                } else
                    printf("Type name doesn't exist.\n");
                break;
            case '5':
                printf("Please enter Pokemon type name:\n");
                char type_opponent[Buffer];
                scanf("%s", type_opponent);
                PType *temp_opponent = getTypeIfExist(type_opponent, Types, numberOfTypes);
                if (temp_opponent == NULL) {
                    printf("Type name doesn't exist.\n");
                    break;
                }
                printf("Please enter Pokemon name:\n");
                char name_opponent[Buffer];
                scanf("%s", name_opponent);
                printf("Please enter Pokemon species:\n");
                char species_opponent[Buffer];
                scanf("%s", species_opponent);
                printf("Please enter Pokemon height:\n");
                float height_opponent;
                scanf("%f", &height_opponent);
                printf("Please enter Pokemon weight:\n");
                float weight_opponent;
                scanf("%f", &weight_opponent);
                printf("Please enter Pokemon attack:\n");
                int attack_opponent;
                scanf("%d", &attack_opponent);

                Pokemon *new_opponent = NULL;
                new_opponent = Create_Pokemon(name_opponent, species_opponent, height_opponent,
                                                       weight_opponent, attack_opponent, temp_opponent);
                if (new_opponent == NULL){
                    printf("No memory available.\n");
                    safeExit(b, Types, numberOfTypes);
                }
                printf("You choose to fight with:\n");
                PokemonToString(new_opponent);
                if (counter_how_many_pokemons_in_battle == 0) {
                    printf("There are no Pokemons to fight against you.\n");
                    deletePokemon(new_opponent);
                    break;
                }
                Pokemon *best_for_fight = NULL;
                best_for_fight = fight(b, new_opponent);

                if (best_for_fight != NULL) {
                    PokemonToString(best_for_fight);
                }

                deletePokemon(new_opponent);
                break;
            case '6':
                safeExit(b, Types, numberOfTypes);
                flag = false;
                break;
            default:
                printf("Please choose a valid number.\n");
                break;

        }
    }
    printf("All the memory cleaned and the program is safely closed.\n");
}

// Building the program data structures according to the data in the configuration text file.
Battle Pokedex_builder(int numberOfTypes, int CapacityOfType, int *total_num_of_pokemons, PType **pPTypes_list,
                       char *configurationTextFile) {
    if (pPTypes_list == NULL || configurationTextFile == NULL) {
        return NULL;
    }

    // Opening file for reading                                                                    //
    // Cross-function declarations (line and token variables are important to all function parts). //
    // Initializations for Type-creation:                   //

    FILE *file;
    file = fopen(configurationTextFile, "r");
    char line[Buffer];
    char *token = NULL;
    char *typename = NULL;
    char *typeline = NULL;


    // Ignoring first line (header - "Types"):              //
    fgets(line, Buffer, file); // Types
    fgets(line, Buffer, file); // Types list
    strtok(line, "\r\n");

    Battle battle;
    battle = createBattleByCategory(CapacityOfType, numberOfTypes, line, (equalFunction) isEqualPokemon,
                                           (copyFunction) copyPokemon, (freeFunction) deletePokemon,
                                           (getCategoryFunction) getTypeName, (getAttackFunction) getAttack,
                                           (printFunction) PokemonToString);

    token = strtok(line, ",");
    typename = token;
    pPTypes_list[0] = Create_Pokemon_Type(typename);

    // Creating all pokemon types left in Types line:       //
    for (int i = 1; i < numberOfTypes; ++i) {
        token = strtok(NULL, ",");
        typename = token;

        // Remove unwanted characters:
        if (strstr(typename, "\r") != NULL) {
            typename[strlen(typename) - 2] = '\0';
        }
        pPTypes_list[i] = Create_Pokemon_Type(typename);
    }

    // Initializations for types lists:
    char *source_type = "";
    char *whichList = NULL;

    // Iteration all over "effective-against" lines:
    while (strstr(source_type, "Pokemons") == NULL) {
        fgets(line, Buffer, file);
        token = strtok(line, "\n");
        typeline = token;

        // Which source type to pass as argument:
        source_type = strtok(typeline, " ");

        if (strstr(source_type, "Pokemons") != NULL)
            continue;

        // Remove unwanted characters:
        if (source_type[0] == '\t') {
            memmove(source_type, source_type + 1, strlen(source_type));
        }

        // Skip the "junk" data:
        token = strtok(NULL, "-");
        token = strtok(NULL, "-");
        token = strtok(NULL, ":");
        whichList = token;

        // Entering data into types lists:
        char *t = NULL;
        while (token != NULL) {
            token = strtok(NULL, ",");
            t = token;
            if (t == NULL) continue;
            // Remove unwanted characters:
            if (strstr(t, "\r") != NULL) {
                t[strlen(t) - 1] = '\0';
            }
            if (token != NULL) {
                if (strstr(whichList, "me") != NULL) {
                    Insert_into_effective_against_me(source_type, token, pPTypes_list, numberOfTypes);
                } else
                    Insert_into_effective_against_others(source_type, token, pPTypes_list, numberOfTypes);
            }
        }
    }

    // Declarations for Pokemon initialization:
    char *pokemonName = NULL;
    char *pokemonSpecies = NULL;
    float height, weight;
    int attack;
    char *pokemonType;

    // Initialization each Pokemon by separating the given configuration file lines
    // into 6 parts. the information gained sends to sub-functions helps to create
    // the Pokemon "instance" (sub-functions are: -get type-, -BD creation-).
    char compare[Buffer];
    strcpy(compare, line);
    fgets(line, Buffer, file);
    while (strcmp(line, compare) != 0) {
        token = strtok(line, ",");
        pokemonName = token;
        token = strtok(NULL, ",");
        pokemonSpecies = token;
        token = strtok(NULL, ",");
        height = atof(token);
        token = strtok(NULL, ",");
        weight = atof(token);
        token = strtok(NULL, ",");
        attack = (int) atof(token);
        token = strtok(NULL, "\r");
        pokemonType = token;
        PType *type = getTypeIfExist(pokemonType, pPTypes_list, numberOfTypes);
        Pokemon *pok = Create_Pokemon(pokemonName, pokemonSpecies, height, weight, attack, type);
        if(insertObject(battle, pok) == failure){
            deletePokemon(pok);
        } else {
            *total_num_of_pokemons += 1;
        }
        // Update the type counter when new Pokemon is created.
        for (int j = 0; j < numberOfTypes; ++j) {
            if (strcmp(pPTypes_list[j]->type_name, pokemonType) == 0) {
                pPTypes_list[j]->HowManyFromType++;

                // Inserting the new Pokemon's address into the right type list:
                InsertPokemonIntoPokemonListInsideType(pPTypes_list[j], pok);
            }
        }
        strcpy(compare, line);
        fgets(line, Buffer, file);
    }
    fclose(file);
    return battle;
}


// SafeEXit function called by case 6 - or by failure of other cases.
void safeExit(Battle battle, PType **pPTypes_list, int numberOfTypes) {

    // freeing effectiveness lists in any type.
    for (int i = 0; i < numberOfTypes; ++i) {
        deleteEffectiveness(pPTypes_list[i]);
    }
    // freeing types in general.
    for (int i = 0; i < numberOfTypes; ++i) {
        deleteType(pPTypes_list[i]);
    }

    destroyBattleByCategory(battle);

    free(pPTypes_list);
    pPTypes_list = NULL;
}