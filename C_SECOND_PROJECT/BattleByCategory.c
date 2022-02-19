#include "Defs.h"
#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include <string.h>


/// Main structure of this file:
/// The Battle by category structure holds the information:
/// (1) Linked list (every linked list node holds MaxHeap of Pokemons).
// The equal function that the user will pass - is the equal function between Pokemons.
// -> it will be sent directly to the MaxHeap equality function.
/// (2) Equal function - knows how to measure equality between two given elements ~ (Pokemons attack equal func).
// The copy function is "Pokemon deep copy" function.
// -> it will be sent directly to the MaxHeap copy function.
/// (3) Copy function - this function can copy heaps elements ~ (Copy Pokemon).
// The free function that the user will pass - the "delete Pokemon" function.
// -> it will be sent directly to the MaxHeap free function.
/// (4) Free function - knows how to free given element ~ (Delete Pokemon).
// This function from the user is for extracting category name from linked list node.
// it will be sent to linked list "get Category" functionality.
// at some point it changed to extract pokemon type from pokemon instance and sends to heap.
/// (5) Get category function - extracting the category name from linked list node ~ (Pokemons attack equal func).
// will be used for Fight functionality.
/// (6) Get attack function - this function gets Pokemon and extracting its attack.
// the passing function is "Pokemon to string" so it will be sent to heap functionality as well.
// for printing linked list we will use printHeap function - sends from wrapping function in this class.
/// (7) Print function - printing function for heaps element ~ (Pokemon to string).
struct battle_s {
    LinkedList linkedList;
    getCategoryFunction getCategoryFunction;
    getAttackFunction getAttackFunction;
    printFunction printFunction;
    int numberOfCategory;
    char *categoriesNames;
};

Battle createBattleByCategory(int capacity, int numberOfCategories, char *categories, equalFunction equalElement,
                              copyFunction copyElement, freeFunction freeElement, getCategoryFunction getCategory,
                              getAttackFunction getAttack, printFunction printElement) {

    if (categories == NULL || equalElement == NULL || copyElement == NULL || freeElement == NULL ||
        getCategory == NULL || getAttack == NULL || printElement == NULL) {
        return NULL;
    }
    Battle battle = (Battle) malloc(sizeof(struct battle_s));
    if (battle == NULL) {
        return NULL;
    }
    battle->categoriesNames = (char *) malloc(strlen(categories) + 1);
    if (battle->categoriesNames == NULL) {
        free(battle);
        return NULL;
    }
    strcpy(battle->categoriesNames, categories);

    battle->linkedList = createLinkedList((freeFunction) destroyHeap, (getCategoryFunction) getHeapId,
                                          (equalFunction) isEqualHeap, (printFunction) printHeap,
                                          (copyFunction) CopyHeap);
    if(battle->linkedList == NULL){
        return NULL;
    }
    battle->getCategoryFunction = getCategory;
    battle->getAttackFunction = getAttack;
    battle->numberOfCategory = numberOfCategories;
    battle->printFunction = printElement;


    char temp[strlen(categories) + 1];
    strcpy(temp, categories);
    char *namesOfCategories[numberOfCategories];

    namesOfCategories[0] = strtok(temp, ",");
    for (int i = 1; i < numberOfCategories; ++i) {
        namesOfCategories[i] = strtok(NULL, ",");
    }

    for (int i = 0; i < numberOfCategories; ++i) {
        MaxHeap maxHeap = NULL;
        maxHeap = CreateHeap(namesOfCategories[i], capacity, freeElement, equalElement, copyElement,
                             printElement);
        appendNode(battle->linkedList, maxHeap);
    }

    return battle;
}

status destroyBattleByCategory(Battle b) {
    if (b == NULL) {
        return failure;
    }
    destroyList(b->linkedList);
    free(b->categoriesNames);
    free(b);
    b = NULL;
    return success;
}

status insertObject(Battle b, element elem) {
    if (b == NULL || elem == NULL) {
        return failure;
    }
    char *TypeName = b->getCategoryFunction(elem);
    MaxHeap temp = searchByKeyInList(b->linkedList, TypeName);
    if (temp != NULL) {
        if (getHeapCurrentSize(temp) == getMaxCapacity(temp)) {
            return failure;
        }
        /// not in maximum capacity:
        insertToHeap(temp, elem);
        return success;
    }
    return failure;
}

void displayObjectsByCategories(Battle b) {
    displayList(b->linkedList);
}

element removeMaxByCategory(Battle b, char *category) {
    MaxHeap temp = searchByKeyInList(b->linkedList, category);
    if (temp != NULL && getHeapCurrentSize(temp) != 0) {
        Element t = PopMaxHeap(temp);
        return t;
    }
    return NULL;
}

int getNumberOfObjectsInCategory(Battle b, char *category) {
    MaxHeap temp = searchByKeyInList(b->linkedList, category);
    return getHeapCurrentSize(temp);
}

element fight(Battle b, element elem) {
    if (b == NULL || elem == NULL) {
        return NULL;
    }
    if (getCurrentSize(b->linkedList) == 0) {
        return NULL;
    }

    int max = -1000000;
    int first_attack_after_manipulates;
    int second_attack_after_manipulates;
    element best = NULL;
    int attack1 = 0;
    int attack2 = 0;

    char temp[Buffer];
    strcpy(temp, b->categoriesNames);
    char *namesOfCategories[b->numberOfCategory];

    namesOfCategories[0] = strtok(temp, ",");
    for (int i = 1; i < b->numberOfCategory; ++i) {
        namesOfCategories[i] = strtok(NULL, ",");
    }

    for (int i = 0; i < b->numberOfCategory; ++i) {
        element temp_pokemon = TopMaxHeap(searchByKeyInList(b->linkedList, namesOfCategories[i]));
        if (temp_pokemon == NULL) {
            continue;
        }
        int diff = b->getAttackFunction(temp_pokemon, elem, &first_attack_after_manipulates,
                                        &second_attack_after_manipulates);
        if (diff > max) {
            max = diff;
            attack1 = first_attack_after_manipulates;
            attack2 = second_attack_after_manipulates;
            best = TopMaxHeap(searchByKeyInList(b->linkedList, namesOfCategories[i]));
        }
    }

    printf("The final battle between:\n");
    b->printFunction(elem);
    printf("In this battle his attack is :%d\n\n", attack2);
    printf("against ");
    b->printFunction(best);
    printf("In this battle his attack is :%d\n\n", attack1);

    if (max > 0) {
        printf("THE WINNER IS:\n");
        return best;
    } else if (max < 0) {
        printf("THE WINNER IS:\n");
        return elem;
    } else
        printf("IT IS A DRAW.\n");
    return NULL;
}


