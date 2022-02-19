//
// Created by ise on 12/31/21.
//

#include "ChickenFarm.h"
#include "Chicken.h"
#include "Costs.h"


ChickenFarm::ChickenFarm() {

    ///each farm starts the game with 10 dollars:
    this->addMoneyToFarm(10);

    ///each farm starts the game with 3 animals:
    for (int i = 0; i < 3; ++i) {
        Animal *cow = new Chicken();
        this->addAnimalToFarm(cow);
    }
}

void ChickenFarm::PrintFarm() {
    std::cout << "Farm Id: " << this->getFarmID() << ", type: Chicken Farm, Money: " <<
              this->getFarmMoney() << ", Animals: " << this->getNumberOfAnimalsInFarm() << " chickens, Products: " <<
              "Milk[0], Wool[" << getNumOfProducts_Desired() << "], Eggs[" << this->getNumOfProducts_Produced() <<
              "]" << std::endl;
}

///Handle functions:
void ChickenFarm::handleCowFarm(Farm *farm) { farm->ChickenFarmWantsToHaveMe(this); }
void ChickenFarm::handleSheepFarm(Farm *farm) {}//do nothing
void ChickenFarm::handleChickenFarm(Farm *farm) {}//do nothing

///Want me functions:
void ChickenFarm::CowFarmWantsToHaveMe(Farm *farm) {}//do nothing
void ChickenFarm::SheepFarmWantsToHaveMe(Farm *farm) { farm->addClient(this); }
void ChickenFarm::ChickenFarmWantsToHaveMe(Farm *farm) {}//do nothing

void ChickenFarm::addClient(Farm *farm) {
    Farm::addClient(farm);
    std::cout << "Chicken farm(" << this->getFarmID() << ") Added Cow farm(" <<
              farm->getFarmID() << ") to his client list" << std::endl;
}

void ChickenFarm::BuyAnimals() {
    int count = 0;
    int current_amount = this->getFarmMoney();
    while (current_amount >= Chicken::getPrice()) {
        Animal *new_chicken = new Chicken();
        this->reduceMoneyFromFarm(Chicken::getPrice());
        this->addAnimalToFarm(new_chicken);
        current_amount -= Chicken::getPrice();
        count++;
    }
    if (count > 0) {
        std::cout << "Chicken farm(" << this->getFarmID() << ") bought " << count << " chickens for "
                  << count * Chicken::getPrice()
                  << " dollars"
                  << std::endl;
    }
}

void ChickenFarm::trade() {
    int count = 0;
    for (int i = 0; i < this->getNumberOfClients(); ++i) {
        while (this->getNumOfProducts_Produced() > 0 && this->MyClients[i]->getFarmMoney() >= EggCost) {

            this->addMoneyToFarm(EggCost);
            this->MyClients[i]->reduceMoneyFromFarm(EggCost);
            ///updating the counters:
            this->removeProducts_Produced(1);
            this->MyClients[i]->addProducts_Desired(1);

            count++;
        }
        if (count > 0) {
            std::cout << "Cow farm(" << this->MyClients[i]->getFarmID() << ") bought " << count << " eggs for " <<
                      count * EggCost << " dollars from Chicken farm(" << this->getFarmID() << ")" << std::endl;
            count = 0;
        }
    }
}

