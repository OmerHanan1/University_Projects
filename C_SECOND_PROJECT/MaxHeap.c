// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021

#include <string.h>
#include "MaxHeap.h"

/// Main structure of this file:
/// The MaxHeap structure holds the information:
/// (1) Heap name.
/// (2) Heaps current capacity.
/// (3) Heaps maximum capacity.
/// (4) The heaps array- declared as void**, which uses as array of elements.
/// (5) Free function - knows how to free given element ~ (Delete Pokemon).
/// (6) Equal function - knows how to measure equality between two given elements ~ (Pokemons attack equal func).
/// (7) Copy function - this function can copy heaps elements ~ (Copy Pokemon).
/// (8) Print function - printing function for heaps element ~ (Pokemon to string).
struct MaxHeap_t {
    char *HeapName;
    int CurrentSize;
    int MaxCapacity;
    Element *HeapArray;
    freeFunction freeFunction;
    equalFunction equalFunction;
    copyFunction copyFunction;
    printFunction printFunction;
};

/// Function for creating new Maximum Heap -
/// Input : (1)name, (2)maximum capacity, (3)free function, (4)equal function, (5)copy function, (6)print function.
/// Output : Initialized linked list address.
MaxHeap CreateHeap(char *HeapName, int MaxHeapCapacity, freeFunction freeFunction, equalFunction equalFunction,
                   copyFunction copyFunction, printFunction printFunction) {
    // Checking the validity of arguments:
    if (HeapName == NULL || freeFunction == NULL || equalFunction == NULL) {
        return NULL;
    }

    // In case of the maximum capacity is not correct.
    if (MaxHeapCapacity <= 0) {
        return NULL;
    }

    // Allocation of memory, and checking whether memory has been allocated correctly
    struct MaxHeap_t *maxHeap = (struct MaxHeap_t *) calloc(1, sizeof(struct MaxHeap_t));
    if (maxHeap == NULL) {
        return NULL;
    }

    // Allocation of memory, and checking whether memory has been allocated correctly
    maxHeap->HeapName = (char *) malloc(sizeof(char) * strlen(HeapName) + 1);
    if (maxHeap->HeapName == NULL) {
        free(maxHeap);
        return NULL;
    }

    // Allocation of memory, and checking whether memory has been allocated correctly
    // I malloced with +1 because of using the explicit place values as indexes (ignore the 0 index)-
    maxHeap->HeapArray = (Element *) malloc((sizeof(Element) * MaxHeapCapacity) + 1);
    if (maxHeap->HeapArray == NULL) {
        free(maxHeap->HeapName);
        free(maxHeap);
        return NULL;
    }

    // Initializing the rest of fields:
    strcpy(maxHeap->HeapName, HeapName);
    maxHeap->CurrentSize = 0;
    maxHeap->MaxCapacity = MaxHeapCapacity;
    maxHeap->freeFunction = freeFunction;
    maxHeap->copyFunction = copyFunction;
    maxHeap->printFunction = printFunction;
    maxHeap->equalFunction = equalFunction; /// 1 first bigger, 0 same, -1 second bigger. (Defs.h)

    // Returns the initialized Maximum Heap:
    return maxHeap;
}

/// Max heapify is the operation make to keep the heap's array build correct.
/// Input : (1)maxHeap, (2)index.
/// Output : void. (changing the order of the elements in the heap's array only).
static void MaxHeapify(MaxHeap maxHeap, int index) {
    // No need to check the legality of given arguments.
    // declaration of "left", "right", "largest" indexes.
    int left = 2 * index;
    int right = (2 * index) + 1;
    int largest;

    //check the validity of the indexes and makes comparisons using equalFunction.
    if (left <= maxHeap->CurrentSize &&
        maxHeap->equalFunction(maxHeap->HeapArray[left], maxHeap->HeapArray[index]) == 1) {
        largest = left;
    } else {
        largest = index;
    }

    if (right <= maxHeap->CurrentSize &&
        maxHeap->equalFunction(maxHeap->HeapArray[right], maxHeap->HeapArray[largest]) == 1) {
        largest = right;
    }
    if (largest != index) {
        Element temp = maxHeap->HeapArray[index];
        maxHeap->HeapArray[index] = maxHeap->HeapArray[largest];
        maxHeap->HeapArray[largest] = temp;

        // Recursive call.
        MaxHeapify(maxHeap, largest);
    }
}

/// Destroying heap, for destroy the heap totally, we use the "FreeFunction" ~
/// for consistency : (known as delete pokemon in this H.W).
/// Input : (1)maxHeap.
/// Output : status.
status destroyHeap(MaxHeap maxHeap) {
    if (maxHeap == NULL) {
        return failure;
    }
    for (int i = 0; i <= maxHeap->MaxCapacity; ++i) {
        if (maxHeap->HeapArray[i] != NULL) {
            maxHeap->freeFunction(maxHeap->HeapArray[i]);
        }
    }
    free(maxHeap->HeapArray);
    free(maxHeap->HeapName);
    free(maxHeap);
    maxHeap = NULL;
    return success;
}

/// This function insert new element into the maxHeap.
/// the algorithm works by steps:
/// Check does size allow for another element to be added to the list->
/// Copy the given element (using given copyFunction)->
/// inserting the element to the end of the heap array->
/// swapping the element to his fits place in array.
/// Input : (1)maxHeap, (2)element ~(Pokemon to add)
/// Output : status.
status insertToHeap(MaxHeap maxHeap, Element element) {
    // Check legality of arguments:
    if (maxHeap == NULL || element == NULL) {
        return failure;
    }

    // Check that the array is not full:
    if (maxHeap->CurrentSize == maxHeap->MaxCapacity) {
        return failure;
    }

    // Copying the element.
    Element element1 = maxHeap->copyFunction(element);

    // In case the maxHeap is empty- adding the element into the first place.
    if (maxHeap->CurrentSize == 0) {
        maxHeap->HeapArray[1] = element1;
        maxHeap->CurrentSize++;
        return success;
    }

    // In case the maxHeap isn't empty - add the element to the ent of the list:
    maxHeap->CurrentSize++;
    int index = maxHeap->CurrentSize;
    maxHeap->HeapArray[maxHeap->CurrentSize] = element1;

    // Swapping the element till it gets to its right place.
    while ((index > 1) && (maxHeap->equalFunction(maxHeap->HeapArray[index / 2], maxHeap->HeapArray[index])) == -1) {
        Element temp_parent = maxHeap->HeapArray[index / 2];
        Element temp_child = maxHeap->HeapArray[index];
        maxHeap->HeapArray[index] = temp_parent;
        maxHeap->HeapArray[index / 2] = temp_child;
        index = index / 2;
    }
    return success;
}

/// Popping the most valuate element in the heap (stored in first index).
/// Input : (1)maxHeap.
/// Output : maximum value element / NULL in case the maxHeap empty.
Element PopMaxHeap(MaxHeap maxHeap) {
    // CHeck the legality of arguments:
    if (maxHeap == NULL) {
        return NULL;
    }

    // if the heap is empty - return NULL:
    if (maxHeap->CurrentSize == 0) {
        return NULL;
    }

    // takes the element in the first place (maximum value element):
    Element maximum = maxHeap->HeapArray[1];
    maxHeap->HeapArray[1] = maxHeap->HeapArray[maxHeap->CurrentSize];
    maxHeap->HeapArray[maxHeap->CurrentSize] = NULL;
    maxHeap->CurrentSize--;

    // Sends the maxHeap to MaxHeapify function for re-order it.
    MaxHeapify(maxHeap, 1);

    // returns the maximum value element.
    return maximum;
}

/// View of the maxHeap maximum value element (not popping it out of heap).
/// Input : (1)maxHeap.
/// Output : element.
Element TopMaxHeap(MaxHeap maxHeap) {
    // CHecking arguments:
    if (maxHeap == NULL) {
        return NULL;
    }

    // Check if the heaps array is empty -> returns NULL (not such an element).
    if (maxHeap->CurrentSize == 0) {
        return NULL;
    }

    // returns a copy of the maxHeap maximum value element.
    return maxHeap->copyFunction(maxHeap->HeapArray[1]);
}

/// This function gets the heaps ID.
/// Input : (1)Maximum heap.
/// Output : string : name of the heap.
char *getHeapId(MaxHeap maxHeap) {
    // Checking the argument.
    if (maxHeap == NULL) {
        return NULL;
    }

    // returns the maxHeaps name.
    return maxHeap->HeapName;
}

/// This function gets the maximum heap's array current size.
/// in ant problem - returns -1.
/// Input : (1)Maximum heap.
/// Output : int the number of current elements in heap.
int getHeapCurrentSize(MaxHeap maxHeap) {
    // check argument validity:
    if (maxHeap == NULL) {

        // If the given argument will be NULL - return value will be -1.
        return -1;
    }

    // returns the maxHeap current size.
    return maxHeap->CurrentSize;
}

/// Printing the heaps elements - from most value elements to least value elements.
/// Input : (1)maxHeap.
/// Output : void (printing to console).
void printHeap(MaxHeap maxHeap) {
    // checking the validity of the argument:
    if (maxHeap == NULL) {
        return;
    }
    // Printing format:
    printf("%s:\n", maxHeap->HeapName);
    if (maxHeap->CurrentSize == 0) {
        printf("No elements.\n\n");
    } else {
        int current = maxHeap->CurrentSize;
        Element temp[maxHeap->CurrentSize + 1];
        MaxHeap t = (MaxHeap) malloc(sizeof(struct MaxHeap_t));

        for (int i = 1; i <= current; ++i) {
            temp[i] = maxHeap->copyFunction(maxHeap->HeapArray[i]);
        }

        t->HeapArray = temp;
        t->CurrentSize = maxHeap->CurrentSize;
        t->equalFunction = maxHeap->equalFunction;

        for (int i = 1; i <= current; ++i) {
            printf("%d. ", i);
            maxHeap->printFunction(PopMaxHeap(t));
        }
        // freeing the temp maxHeap.
        free(t);
    }
}

MaxHeap CopyHeap(MaxHeap maxHeap) {
//    struct MaxHeap_t *new = (struct MaxHeap_t *) malloc(sizeof(struct MaxHeap_t));
//    new->HeapArray = (Element *) malloc(sizeof(Element) * maxHeap->MaxCapacity);
//    new->HeapArray = maxHeap->HeapArray;
//
//    new->CurrentSize = maxHeap->CurrentSize;
//
//    new->HeapName = (char *) malloc(sizeof(char) * strlen(maxHeap->HeapName));
//    new->HeapName = maxHeap->HeapName;
//
//    new->freeFunction = maxHeap->freeFunction;
//    new->equalFunction = maxHeap->equalFunction;
//    new->copyFunction = maxHeap->copyFunction;
//    new->MaxCapacity = maxHeap->MaxCapacity;
//    new->printFunction = maxHeap->printFunction;
//    return new;
    return maxHeap;
}

int isEqualHeap(MaxHeap maxHeap1, MaxHeap maxHeap2) {
    if (strcmp(getHeapId(maxHeap1), getHeapId(maxHeap2)) == 0) {
        return 0;
    }
    return -1;
}


/// UnitTest function:
Element getElementInIndex(MaxHeap maxHeap, int index) {
    return maxHeap->HeapArray[index];
}

/// UnitTest function:
int getMaxCapacity(MaxHeap maxHeap) {
    return maxHeap->MaxCapacity;
}