//
// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"


// Functions declaration:

void safeExit(Pokemon **pPokemons_list, int numberOfPokemons, PType **pPTypes_list, int numberOfTypes);

void Pokedex_builder(int numberOfTypes, int numberOfPokemons, Pokemon **pPokemons_list, PType **pPTypes_list,
                     char *configurationTextFile);

int main(int argc, char *argv[]) {


    // (1) Initialization list of Pokemon Types and list of Pokemons.               //
    // Pokemon Types: a pointer to an array of pointers, each points to type.       //
    // Pokemon Types array will be as big as the first argument value.              //
    // Pokemons: a pointer to an array of pointer, each points to Pokemon.          //
    // Pokemons array will be as big as the second argument value.                  //

    int numberOfTypes = atoi(argv[1]);          //Getting number of types. passed as an argument.
    int numberOfPokemons = atoi(argv[2]);       //Getting number of Pokemons. passed as an argument.
    char *config = argv[3];

    PType **pPTypes_list = NULL;
    Pokemon **pPokemons_list = NULL;
    pPTypes_list = (PType **) malloc(numberOfTypes * sizeof(PType *));
    if (pPTypes_list == NULL) {                         //Checking memory was allocated properly.
        printf("Memory Problem\n"); // TODO: make enum statuses !!!
        return 0;
    }
    pPokemons_list = (Pokemon **) malloc(numberOfPokemons * sizeof(Pokemon *));
    if (pPokemons_list == NULL) {                       //Checking memory was allocated properly.
        printf("Memory Problem\n"); // TODO: make enum statuses !!!
        return 0;
    }

    // (2) The main first focus in the program -                                    //
    // take the arguments passed in the program, and build the Pokedex.             //
    // The Pokedex will contain 2 main values:                                      //
    // -1- Pokemons list. each Pokemon in the list contains:                        //
    //        name                                                                  //
    //        species                                                               //
    //        pointer to biological data                                            //
    //        pointer to type.                                                      //
    // -2- Pokemon Types list. each Type in the list contains:                      //
    //        type name                                                             //
    //        pointer to effective against me list of types                         //
    //        pointer to effective against others list of types                     //

    Pokedex_builder(numberOfTypes, numberOfPokemons, pPokemons_list, pPTypes_list, config);


    // (3) Main menu that runs while running the program.                           //
    // I chose to scan the users choices as char and not as integer,                //
    // it helps problem fixing.                                                     //

    bool flag = true;
    while (flag) {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Add type to effective against me list\n");
        printf("4 : Add type to effective against others list\n");
        printf("5 : Remove type from effective against me list\n");
        printf("6 : Remove type from effective against others list\n");
        printf("7 : Print Pokemon by name\n");
        printf("8 : Print Pokemons by type\n");
        printf("9 : Exit\n");

        char c[Buffer];
        scanf("%s", c);
        if (strlen(c) != 1) c[0] = 0;
        switch (c[0]) {

            case '1':

                // Printing all the Pokemons via printing rules.
                // The function uses a sub-function for printing one Pokemon by rules:
                for (int i = 0; i < numberOfPokemons; ++i) {
                    if(PokemonToString(pPokemons_list[i]) == failure){
                        // In case of memory problem using this case,
                        // The program will exit in the safest way it can.
                        safeExit(pPokemons_list,numberOfPokemons,pPTypes_list, numberOfTypes);
                    }
                }
                break;

            case '2':

                // Printing all the Pokemon Types via printing rules.
                // The function uses a sub-function for printing one Type by rules:
                for (int i = 0; i < numberOfTypes; ++i) {
                    if(TypeToString(pPTypes_list[i]) == failure){
                        // In case of memory problem using this case,
                        // The program will exit in the safest way it can.
                        safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                    }
                }
                break;

            case '3':

                // Adding type to effective against me list
                // The case (3) gets source type and target type,
                // and inserting the target type into the suitable list inside the source type.
                // for example:
                //         source type : "Type1".
                //         target type : "Type2".
                // "Type1"-> effective against me list : "Type2".
                // This case using sub-function : "Insert_into_effective_against_me".
                printf("Please enter type name:\n");
                char temp[Buffer];
                scanf("%s", temp);
                PType *pType = getTypeIfExist(temp, pPTypes_list, numberOfTypes);
                if (pType == NULL) {
                    printf("Type name doesn't exist.\n");
                } else {
                    printf("Please enter type name to add to %s effective against me list:\n", pType->type_name);
                    char typeMe[Buffer];
                    scanf("%s", typeMe);
                    PType *pType2 = getTypeIfExist(typeMe, pPTypes_list, numberOfTypes);
                    if (pType2 == NULL) {
                        printf("Type name doesn't exist.\n");
                    } else {
                        bool isExist = false;
                        for (int i = 0; i < pType->HowManyMe; ++i) {
                            if (strcmp(pType2->type_name, pType->effective_against_me[i]->type_name) == 0) {
                                isExist = true;
                            }
                        }
                        if (isExist == true) {
                            printf("This type already exist in the list.\n");
                        } else {
                            if (Insert_into_effective_against_me(pType->type_name, pType2->type_name, pPTypes_list,
                                                                 numberOfTypes) != failure) {
                                TypeToString(pType);
                            }
                            else
                            {
                                // If the run fail, it will print "Memory problem" inside the function.
                                // For exit the safest way, im calling the "safeExit" function.
                                safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                            }
                        }
                    }
                }
                break;
            case '4':

                // Adding type to effective against others list
                // The case (4) gets source type and target type,
                // and inserting the target type into the suitable list inside the source type.
                // for example:
                //         source type : "Type1".
                //         target type : "Type2".
                // "Type1"-> effective against others list : "Type2".
                // This case using sub-function : "Insert_into_effective_against_others".
                printf("Please enter type name:\n");
                char buf[Buffer];
                scanf("%s", buf);
                PType *type1 = getTypeIfExist(buf, pPTypes_list, numberOfTypes);
                if (type1 == NULL) {
                    printf("Type name doesn't exist.\n");
                } else {
                    printf("Please enter type name to add to %s effective against others list:\n", type1->type_name);
                    char buf2[Buffer];
                    scanf("%s", buf2);
                    PType *type2 = getTypeIfExist(buf2, pPTypes_list, numberOfTypes);
                    if (type2 == NULL) {
                        printf("Type name doesn't exist.\n");
                    } else {
                        bool isExist2 = false;
                        for (int i = 0; i < type1->HowManyOther; ++i) {
                            if (strcmp(type2->type_name, type1->effective_against_others[i]->type_name) == 0) {
                                isExist2 = true;
                            }
                        }
                        if (isExist2 == true) {
                            printf("This type already exist in the list.\n");
                        } else {
                            if (Insert_into_effective_against_others(type1->type_name, type2->type_name, pPTypes_list,
                                                                     numberOfTypes) != failure) {
                                TypeToString(type1);
                            }
                            else{
                                // If the run fail, it will print "Memory problem" inside the function.
                                // For exit the safest way, im calling the "safeExit" function.
                                safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                            }
                        }
                    }
                }
                break;
            case '5':

                // Remove type from effective against me list
                // The case (5) gets source type and target type,
                // and removing the target type from the suitable list inside the source type.
                // for example:
                //         source type : "Type1".
                //         target type : "Type2".
                // {Before calling this case} - "Type1"-> effective against me list : "Type2".
                // {After calling this case} - "Type1"-> effective against me list : ---
                // This case using sub-function : "Delete_type_from_effective_against_me_list".
                printf("Please enter type name:\n");
                char b1[Buffer];
                scanf("%s", b1);
                PType *s1 = getTypeIfExist(b1, pPTypes_list, numberOfTypes);
                if (s1 == NULL) {
                    printf("Type name doesn't exist.\n");
                } else {
                    printf("Please enter type name to remove from %s effective against me list:\n", s1->type_name);
                    char b2[Buffer];
                    scanf("%s", b2);
                    PType *s2 = getTypeIfExist(b2, pPTypes_list, numberOfTypes);
                    if (s2 == NULL) {
                        printf("Type name doesn't exist in the list.\n");
                        break;
                    }
                    bool isInList1 = false;
                    for (int i = 0; i < s1->HowManyMe; ++i) {
                        if (strcmp(s2->type_name, s1->effective_against_me[i]->type_name) == 0) {
                            isInList1 = true;
                        }
                    }
                    if (isInList1 == false) {
                        printf("Type name doesn't exist in the list.\n");
                    } else {
                        if (Delete_type_from_effective_against_me_list(s1, s2) != failure) {
                            TypeToString(s1);
                        }
                        else{
                            // If the run fail, it will print "Memory problem" inside the function.
                            // For exit the safest way, im calling the "safeExit" function.
                            safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                        }
                    }
                }
                break;
            case '6':

                // Remove type from effective against others list
                // The case (6) gets source type and target type,
                // and removing the target type from the suitable list inside the source type.
                // for example:
                //         source type : "Type1".
                //         target type : "Type2".
                // {Before calling this case} - "Type1"-> effective against others list : "Type2".
                // {After calling this case} - "Type1"-> effective against others list : ---
                // This case using sub-function : "Delete_type_from_effective_against_others_list".
                printf("Please enter type name:\n");
                char a1[Buffer];
                scanf("%s", a1);
                PType *pt1 = getTypeIfExist(a1, pPTypes_list, numberOfTypes);
                if (pt1 == NULL) {
                    printf("Type name doesn't exist.\n");
                } else {
                    printf("Please enter type name to remove from %s effective against others list:\n", pt1->type_name);
                    char a2[Buffer];
                    scanf("%s", a2);
                    PType *pt2 = getTypeIfExist(a2, pPTypes_list, numberOfTypes);
                    if (pt2 == NULL) {
                        printf("Type name doesn't exist in the list.\n");
                        break;
                    }
                    bool isInList2 = false;
                    for (int i = 0; i < pt1->HowManyOther; ++i) {
                        if (strcmp(pt2->type_name, pt1->effective_against_others[i]->type_name) == 0) {
                            isInList2 = true;
                        }
                    }
                    if (isInList2 == false) {
                        printf("Type name doesn't exist in the list.\n");
                    } else {
                        if (Delete_type_from_effective_against_others_list(pt1, pt2) != failure) {
                            TypeToString(pt1);
                        }
                        else{
                            // If the run fail, it will print "Memory problem" inside the function.
                            // For exit the safest way, im calling the "safeExit" function.
                            safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                        }
                    }
                }
                break;
            case '7':

                // Print Pokemon by name
                // The case (7) gets string of Pokemon name,
                // and prints the fit Pokemon.
                printf("Please enter Pokemon name:\n");
                char temp2[Buffer];
                scanf("%s", temp2);
                Pokemon *pokemon = getPokemonIfExist(temp2, pPokemons_list, numberOfPokemons);
                if (pokemon != NULL) {
                    if (PokemonToString(pokemon) == failure){
                        // If the run fail, it will print "Memory problem" inside the function.
                        // For exit the safest way, im calling the "safeExit" function.
                        safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                    }
                } else
                    printf("The Pokemon doesn't exist.\n");
                break;
            case '8':

                // Print Pokemons by Type
                // The case (8) gets string of Pokemon type,
                // and prints the fit Pokemons (all the Pokemons with this type).
                printf("Please enter type name:\n");
                char temp3[Buffer];
                scanf("%s", temp3);
                PType *type = getTypeIfExist(temp3, pPTypes_list, numberOfTypes);
                if (type != NULL) {
                    if (type->HowManyFromType != 0) {
                        printf("There are %d Pokemons with this type:\n", type->HowManyFromType);
                        for (int i = 0; i < type->HowManyFromType; ++i) {
                            if(PokemonToString(type->pPokemon[i]) == failure){
                                // If the run fail, it will print "Memory problem" inside the function.
                                // For exit the safest way, im calling the "safeExit" function.
                                safeExit(pPokemons_list,numberOfPokemons,pPTypes_list,numberOfTypes);
                            }
                        }
                    } else
                        printf("There are no Pokemons with this type.\n");
                } else
                    printf("Type name doesn't exist.\n");
                break;
            case '9':

                // This case (9) calls the important function "safeExit".
                // safeExit function cleans all the memory allocated to this application while used,
                // After that, exit the program.
                safeExit(pPokemons_list, numberOfPokemons, pPTypes_list, numberOfTypes);
                flag = false;
                break;
            default:
                printf("Please choose a valid number.\n");
                break;
        }
    }
    printf("All the memory cleaned and the program is safely closed.\n");
    return 0; // Safe exit.
}

// Building the program data structures according to the data in the configuration text file.
void Pokedex_builder(int numberOfTypes, int numberOfPokemons, Pokemon **pPokemons_list, PType **pPTypes_list,
                     char *configurationTextFile) {
    if (pPokemons_list == NULL || pPTypes_list == NULL || configurationTextFile == NULL){
        printf("Memory Problem");
        return;
    }

    // Opening file for reading                                                                    //
    // Cross-function declarations (line and token variables are important to all function parts). //
    FILE *file;
    file = fopen(configurationTextFile, "r");
    char line[Buffer];
    char *token = NULL;

    // Ignoring first line (header - "Types"):              //
    fgets(line, Buffer, file);

    // Changing it in the end to start scanning only when "Types" header appears. //

    // Initializations for Type-creation:                   //
    char *typename = NULL;
    char *typeline = NULL;

    // Creating the first Pokemon Type:                     //
    fgets(line, Buffer, file);
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
    for (int i = 0; i < numberOfPokemons; ++i) {
        fgets(line, Buffer, file);
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
        pPokemons_list[i] = pok;

        // Update the type counter when new Pokemon is created.
        for (int j = 0; j < numberOfTypes; ++j) {
            if (strcmp(pPTypes_list[j]->type_name, pokemonType) == 0) {
                pPTypes_list[j]->HowManyFromType++;

                // Inserting the new Pokemon's address into the right type list:
                InsertPokemonIntoPokemonListInsideType(pPTypes_list[j], pok);
            }
        }
    }
    fclose(file);
}


// SafeEXit function called by case 9 - or by failure of other cases.
void safeExit(Pokemon **pPokemons_list, int numberOfPokemons, PType **pPTypes_list, int numberOfTypes) {

    // freeing effectiveness lists in any type.
    for (int i = 0; i < numberOfTypes; ++i) {
        deleteEffectiveness(pPTypes_list[i]);
    }
    // freeing types in general.
    for (int i = 0; i < numberOfTypes; ++i) {
        deleteType(pPTypes_list[i]);
    }
    // freeing all Pokemons in general.
    for (int i = 0; i < numberOfPokemons; ++i) {
        deletePokemon(pPokemons_list[i]);
    }

    // Deletes the "Main Lists" of the program.
    free(pPokemons_list);
    pPokemons_list = NULL;
    free(pPTypes_list);
    pPTypes_list = NULL;
}

