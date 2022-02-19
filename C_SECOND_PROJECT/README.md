
# Pokemon's Project - part 2
 C project - Advanced programming course

This project was done as part of the “Advanced programming course”.
the aim of the project is to create and use structs, pointers (include function pointers to data-sigment), memory allocations, 
building generic ADT's such as: maximum heap, linked list.
This project is about building generic abstract data types in C programming lang.
this project including modules such as:

Defs.h: definitions header.

Pokemon.h/ Pokemon.c: pokemon module header and source files.

MaxHeap.h/ MaxHeap.c: generic maximum heap header and source files.

LinkedList.h/ LinkedList.c: genericLinked list header and source files.

BattleByCategory.h/.c: generic ADT that can generates fights between struct objects that support the requirements (such as Pokemons module).

MainSeconf.c: the main file for this project (second). this file includes 3 main functions:
  1. Pokedex builder - initializing the data structures from the given text file.
  2. Main - related menu.
  3. Deletion - deleting all memory allocations to prevent memory leaks.

### The code was checked with Valgrind memory leaks checker - memory leaks free code.
