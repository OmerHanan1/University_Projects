// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021


#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Defs.h"

/// The struct implementation is written in the C file,
/// letting the implementation be secured.
/// for using the LinkedList struct and function, user can use the
/// pointer - "LinkedList" as described here:
typedef struct LinkedList_t *LinkedList;

/// Generic LinkedList element - declaration:
typedef void *Element;

/// Creating LinkedList: this function gets all the information needed to
/// build and initialized a new linked list- attributes and functions,
/// and returns a pointer (address of) the new LinkedList.
/// The free/equal/print declarations are in the Defs.h file.
LinkedList createLinkedList(freeFunction freeFunction, getCategoryFunction getKey,
                            equalFunction isEqualFunction, printFunction printFunction, copyFunction copyFunction);

/// Destroying LinkedList: this function gets pointer (address of) LinkedList
/// and by using given free function that is suitable for the element type stored in,
/// freeing all the data allocated in memory for this structure.
status destroyList(LinkedList linkedList);

/// Appending new element to the list: this function gets pointer (address of) LinkedList,
/// and an element we want to add into the list.
/// The function will add the element to the end of the given LinkedList.
status appendNode(LinkedList linkedList, Element element);

/// Deletion of node from the list: this function gets pointer (address of) LinkedList,
/// and an element (that already stored in the list)- and the function removing this element
/// from the node it stored in, and freeing the related allocated memory.
/// this function should use "search method" from the ADT user.
status deleteNode(LinkedList linkedList, Element element);

/// Display list: this function prints the LinkedList elements by given printing format.
/// This function uses a printing method given by the ADT user.
void displayList(LinkedList linkedList);

/// Searching elements by key in the list: this function iterates the LinkedList
/// elements to find if the given element value is stored inside the LinkedList.
/// The function gets by arguments pointer (address of) LinkedList and a pointer
/// (address of) some key -also element to search.
Element searchByKeyInList(LinkedList linkedList, Element element);

/// Gets the linked list current size.
int getCurrentSize(LinkedList linkedList);
void setCurrentSize(LinkedList linkedList, int number);

#endif