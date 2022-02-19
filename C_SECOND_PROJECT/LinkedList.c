// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021

#include "LinkedList.h"
#include <string.h>

/// Auxiliary structure:
/// The Node_t structure is holding:
/// (1) element data,
/// (2) address of the next node in list
typedef struct Node_t {
    Element value;
    struct Node_t *next;
} Node;

/// Main structure of this file:
/// The LinkedList structure holds the information:
/// (1) Size of the list.
/// (2) Address of the head of list.
/// (3) Address of the last node of the list.
/// (4) Free function - knows how to delete given element ~ (destroy heap).
/// (5) Get key function - knows how to extract given elements key ~ (get heaps id).
/// (6) Is equal function - knows to measure equality between two linked list elements ~ (heaps id's equality).
/// (7) Print function - this function can print the linked list elements ~ (display heap).
/// (8) Copy function - deep copy of the linked list elements ~ (copy heap).
struct LinkedList_t {
    int size;
    Node *head;
    Node *end;
    freeFunction freeFunction;
    getCategoryFunction getKey;
    equalFunction isEqualFunction;
    printFunction printFunction;
    copyFunction copyFunction;
};

/// Function for creating new LinkedList -
/// Input : (1)free function, (2)getKey function, (3)isEqual function, (4)print function, (5)copy function.
/// Output : Initialized linked list address.
LinkedList createLinkedList(freeFunction freeFunction, getCategoryFunction getKey,
                            equalFunction isEqualFunction, printFunction printFunction, copyFunction copyFunction) {
    // Checking that the given arguments are legal:
    if (freeFunction == NULL || getKey == NULL || isEqualFunction == NULL ||  printFunction == NULL) {
        return NULL;
    }
    // Allocating memory for the linked list, and checking that the memory allocated correctly:
    struct LinkedList_t *linkedList = (struct LinkedList_t *) malloc(sizeof(struct LinkedList_t));
    if (linkedList == NULL) {
        return NULL;
    }
    // Initializing linked list attributes:
    linkedList->size = 0;
    linkedList->head = NULL;
    linkedList->end = NULL;
    linkedList->freeFunction = freeFunction;
    linkedList->getKey = getKey;
    linkedList->isEqualFunction = isEqualFunction;
    linkedList->printFunction = printFunction;
    linkedList->copyFunction = copyFunction;

    // returning the LinkedList address (as described):
    return linkedList;
}

/// Function for destroying given LinkedList:
/// Input : (1)address of linked list to remove.
/// Output : void.
status destroyList(LinkedList linkedList) {
    // Checking that the given arguments are legal:
    if (linkedList == NULL) {
        return failure;
    }
    // Deleting the inner data of the node - the Element stored inside-
    Node *current = linkedList->head;
    for (int i = 0; i < linkedList->size; ++i) {
        // Using the given free function for removing element:
        linkedList->freeFunction(current->value);
        current = current->next;
    }
    // Deleting the node itself from the list-
    current = linkedList->head;
    while (current != NULL) {
        Node *temp = current->next;
        free(current);
        current = temp;
    }
    // Deleting the rest of fields-
    linkedList->head = NULL;
    linkedList->end = NULL;
    free(linkedList);
    linkedList = NULL;
    return success;
}

/// Function use for appending new node to the end of given list:
/// Inputs : (1)linked list, (2)element.
/// Outputs : status.
status appendNode(LinkedList linkedList, Element element) {
    // Checking that the given arguments are legal:
    if (linkedList == NULL || element == NULL) {
        return failure;
    }
    // Allocating memory for the node, and checking that the memory allocated correctly:
    Node *new = (Node*) malloc(sizeof(Node));
    if (new == NULL) {
        return failure;
    }
    new->next = NULL;
//    new->value = linkedList->copyFunction(element);
    new->value = linkedList->copyFunction(element);
    if(new->value == NULL){
        free(new);
        return failure;
    }
    if(linkedList->size == 0){
        linkedList->head = new;
        linkedList->end = new;
        linkedList->size++;
        return success;
    }
    // Sets the new values as should:
    linkedList->end->next = new;
    linkedList->end = new;
    linkedList->size++;

    return success;
}

/// Helping function: this function indicates if some element is
/// inside the list.
/// Input : (1)linked list, (2)element.
/// Output : true/false- boolean value.
/// The indication about if some element holds the same value of one of the nodes we have in list,
/// will be given by the user as "isEqualFunction".
static bool IsExist(LinkedList linkedList, Element element) {
    // No need to check that the given arguments are legal.

    // Current node holds the linked list head.
    Node *current = linkedList->head;

    // Iterating the linked list nodes and check equality to given element.
    while (current != NULL) {
        if (linkedList->isEqualFunction(current->value, element) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

/// This function use for delete nodes in the lined list.
/// it splits to 3 optional cases:
/// first case - the deletion node is the head of the linked list
/// second case - the deletion node is the end of the linked list
/// third case - the deletion node is inside the linked list (not edges).
/// Input : (1)linked list, (2)element.
/// Output : status.
status deleteNode(LinkedList linkedList, Element element) {
    // Checking that the given arguments are legal:
    if (linkedList == NULL || element == NULL) {
        return failure;
    }

    // If the element we want to delete isn't exist in list - returns failure status.
    if (IsExist(linkedList, element) == false) {
        return failure;
    }

    // Current holds the head og the linked list.
    Node *current = linkedList->head;

    // In case the element we want to delete - stored in the linked list head.
    if (linkedList->isEqualFunction(linkedList->head->value, element) == 0) {
        linkedList->head = current->next;
        linkedList->freeFunction(current->value);
        free(current);
        linkedList->size--;
        return success;
    }
    // In case the node to delete is the end of the list:
    else if (linkedList->isEqualFunction(linkedList->end->value, element) == 0) {
        //Node *temp = linkedList->head;
        while (current->next != linkedList->end) {
            current = current->next;
        }
        current->next = NULL;
        linkedList->freeFunction(linkedList->end->value);
        free(linkedList->end);
        linkedList->end = current;
        linkedList->size--;
        return success;
    }
    // In case the node to delete is inside the list - not the edges:
    else {
        while(current != NULL){
            if(linkedList->isEqualFunction(current->value, element) == 0){
                break;
            }
            current = current->next;

        }
        Node *previous = linkedList->head;
        while (linkedList->isEqualFunction(previous->next->value, element) != 0) {
            previous = previous->next;
        }
        Node *next = current->next;

        previous->next = next;
        linkedList->freeFunction(current->value);
        linkedList->size--;
        return success;
    }
}

/// This function use for displaying the linked list pass into this function as argument.
/// The functionality of printing the elements correctly is given by user via function "printFunction".
/// Input : (1)linked list.
/// Output : void (prints to console).
void displayList(LinkedList linkedList) {
    // Checking that the given argument is legal:
    if (linkedList == NULL) {
        return;
    }
    // Current node holds the head of the linked list.
    Node *current = linkedList->head;

    // Printing the linked list elements by using the print function given by user:
    while (current != NULL) {
        linkedList->printFunction(current->value);
        current = current->next;
    }
}

/// This function is searching if some "element" is equal to - some specific part of the linked list element.
/// The function that can indicate if some given key value is equal to specific part of the linked list element
/// will be given by the use as "searchFunction".
/// Input : (1)linked list, (2)element (some key value).
/// Output : Element if found, NULL if not.
Element searchByKeyInList(LinkedList linkedList, Element key){
    // Checking that the given arguments are legal:
    if(linkedList == NULL || key == NULL){
        return NULL;
    }

    // Current hold the head of the linked list:
    Node *current = linkedList->head;

    // Using the "get key" function for elements in the linked list.
    // We assume that every element in the linked list have String unique key.
    // After extracting the key, compare it with the argument given key of the function.
    while (current != NULL){
        if(strcmp(linkedList->getKey(current->value),key)==0){
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// this function uses to know what is the current size of the linked list.
int getCurrentSize(LinkedList linkedList){
    int size = linkedList->size;
    return size;
}

void setCurrentSize(LinkedList linkedList, int number){
    linkedList->size = number;
}


