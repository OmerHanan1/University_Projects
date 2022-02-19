PokemonsBattles: BattleByCategory.o LinkedList.o MainSecond.o MaxHeap.o Pokemon.o
	gcc BattleByCategory.o LinkedList.o MainSecond.o MaxHeap.o Pokemon.o -o PokemonsBattles
BattleByCategory.o: BattleByCategory.c Defs.h BattleByCategory.h LinkedList.h MaxHeap.h
	gcc -c BattleByCategory.c 
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MainSecond.o: MainSecond.c Pokemon.h Defs.h BattleByCategory.h
	gcc -c MainSecond.c
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c
Pokemon.o: Pokemon.c Pokemon.h Defs.h
	gcc -c Pokemon.c
clean:
	rm -f *.o
