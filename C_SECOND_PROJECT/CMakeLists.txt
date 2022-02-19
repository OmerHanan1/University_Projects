cmake_minimum_required(VERSION 3.20)
project(C_SECOND_PROJECT C)

set(CMAKE_C_STANDARD 99)

add_executable(C_SECOND_PROJECT MainSecond.c LinkedList.c LinkedList.h MaxHeap.c MaxHeap.h BattleByCategory.c BattleByCategory.h Defs.h Pokemon.c Pokemon.h)
