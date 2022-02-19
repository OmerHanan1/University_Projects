// Author: Omer Hanan
// Pokemon project
// Adv. Prog. course - BGU 2021

#ifndef C_PROJECT_DEFS_H
#define C_PROJECT_DEFS_H

#define Buffer 300
typedef enum e_status {
    success, failure
} status;

//typedef enum e_bool{false,true} bool;

typedef void *element;

typedef element (*copyFunction)(element);

typedef status (*freeFunction)(element);

typedef status (*printFunction)(element);

/// 1 first bigger, 0 same, -1 second bigger.
typedef int(*equalFunction)(element, element);

typedef char *(*getCategoryFunction)(element);

/// returns the first attack-second attack. also produce the attack of each element,
/// The function transmits the information through the pointers received in the function.
typedef int (*getAttackFunction)(element firstElem, element SecondElem, int *attackFirst, int *attackSecond);

#endif //C_PROJECT_DEFS_H
