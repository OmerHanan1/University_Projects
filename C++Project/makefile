CPP_FARM: Animal.o Chicken.o ChickenFarm.o Cow.o CowFarm.o Farm.o farmMarket.o Market.o Sheep.o SheepFarm.o
	g++ Animal.o Chicken.o ChickenFarm.o Cow.o CowFarm.o Farm.o farmMarket.o Market.o Sheep.o SheepFarm.o -o CPP_FARM
farmMarket.o: farmMarket.cpp Market.h Farm.h Animal.h
	g++ -c farmMarket.cpp
Animal.o: Animal.cpp Animal.h
	g++ -c Animal.cpp
Chicken.o: Chicken.cpp Chicken.h Animal.h
	g++ -c Chicken.cpp
ChickenFarm.o: ChickenFarm.cpp ChickenFarm.h Farm.h Animal.h Chicken.h Costs.h
	g++ -c ChickenFarm.cpp
Cow.o: Cow.cpp Cow.h Animal.h
	g++ -c Cow.cpp
CowFarm.o: CowFarm.cpp CowFarm.h Farm.h Animal.h Cow.h Costs.h
	g++ -c CowFarm.cpp
Farm.o: Farm.cpp Farm.h Animal.h
	g++ -c Farm.cpp
Market.o: Market.cpp Farm.h Animal.h CowFarm.h SheepFarm.h ChickenFarm.h Market.h Exceptions.h
	g++ -c Market.cpp
Sheep.o: Sheep.cpp Sheep.h Animal.h
	g++ -c Sheep.cpp
SheepFarm.o: SheepFarm.cpp SheepFarm.h Farm.h Animal.h Sheep.h Costs.h
	g++ -c SheepFarm.cpp
clean:
	rm -f *.o
