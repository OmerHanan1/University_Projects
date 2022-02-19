// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021


#ifndef _MAXHEAP_H
#define _MAXHEAP_H


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Defs.h"

/// The struct implementation is written in the C file,
/// letting the implementation be secured.
/// for using the MaxHeap struct and function, user can use the
/// pointer - "MaxHeap" as described here:
typedef struct MaxHeap_t *MaxHeap;

/// Generic MaxHeap element - declaration:
typedef void *Element;

/// Creating MaxHeap: this function gets all the information needed to
/// build and initialized a new Maximum Heap- attributes and functions,
/// and returns a pointer (address of) the new Maximum Heap.
/// The free/equal declarations are in the Defs.h file.
MaxHeap CreateHeap(char *HeapName, int MaxHeapCapacity, freeFunction freeFunction, equalFunction equalFunction,
                   copyFunction copyFunction, printFunction printFunction);

/// Destroying MaxHeap: this function gets pointer (address of) MaxHeap
/// and by using given free function that is suitable for the element type stored in,
/// freeing all the data allocated in memory for this structure.
status destroyHeap(MaxHeap maxHeap);

/// Inserting new "Heap element" to the MaxHeap: this function gets pointer (address of) MaxHeap,
/// and an element we want to add into the Heap.
/// The function will add the element to the Maximum Heap.
status insertToHeap(MaxHeap maxHeap, Element element);

/// Print Heap: this function prints the Maximum Heap elements by given printing format.
void printHeap(MaxHeap maxHeap);

/// This function popping the maximum value element from the MaxHeap.
/// The function is taking the maximum value element in the heap, pop it out,
/// the item we found will return by address and also will be deleted from heap.
/// afterwards, send the Heap to MaxHeapify inner static method for re-organize the HeapArray.
/// If the Heap is empty - the function will return NULL.
Element PopMaxHeap(MaxHeap maxHeap);

/// This function gives the maximum value heap element (as described in "popMaxHeap" function),
/// the maximum value comparison criterion will be determined by user given function.
/// Unlike the "PopMaxHeap" function, we will not pop this item and will not delete it from heap.
Element TopMaxHeap(MaxHeap maxHeap);

/// This function gets by argument a pointer (address of) Maximum heap.
/// the function returns the Maximum heap name (one of the Heap's attributes).
char *getHeapId(MaxHeap maxHeap);

/// This function gets by argument a pointer (address of) Maximum Heap.
/// the function returns the Maximum Heap current size (one of the Heap's attributes).
int getHeapCurrentSize(MaxHeap maxHeap);

MaxHeap CopyHeap(MaxHeap maxHeap);
int isEqualHeap(MaxHeap maxHeap1, MaxHeap maxHeap2);

/// By given maxHeap and index, the function returns the element that
/// stored in the index place at the maxHeap Array.
/// This function uses for UnitTest class.
Element getElementInIndex(MaxHeap maxHeap, int index);

/// By given MaxHeap, the function returns the maximum capacity allowed
/// This function uses for UnitTest class.
int getMaxCapacity(MaxHeap maxHeap);

#endif