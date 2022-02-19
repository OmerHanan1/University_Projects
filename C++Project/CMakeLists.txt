cmake_minimum_required(VERSION 3.20)
project(CPP_PROJECT)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP_PROJECT farmMarket.cpp Farm.cpp Farm.h Animal.cpp Animal.h Cow.cpp Cow.h Sheep.cpp Sheep.h
        Chicken.cpp Chicken.h CowFarm.cpp CowFarm.h SheepFarm.cpp SheepFarm.h ChickenFarm.cpp ChickenFarm.h
        Market.cpp Market.h Exceptions.h Costs.h)
