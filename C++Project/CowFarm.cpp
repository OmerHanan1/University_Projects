//
// Created by ise on 12/31/21.
//
#include "CowFarm.h"
#include "Cow.h"
#include "Costs.h"

CowFarm::CowFarm() {

    ///each farm starts the game with 10 dollars:
    this->addMoneyToFarm(10);

    ///each farm starts the game with 3 animals:
    for (int i = 0; i < 3; ++i) {
        Animal *cow = new Cow();
        this->addAnimalToFarm(cow);
    }
}

void CowFarm::PrintFarm() {
    std::cout << "Farm Id: " << this->getFarmID() << ", type: Cow farm, Money: " <<
              this->getFarmMoney() << ", Animals: " << this->getNumberOfAnimalsInFarm() << " cows, Products: " <<
              "Milk[" << this->getNumOfProducts_Produced() << "], Wool[0], Eggs[" << this->getNumOfProducts_Desired() <<
              "]" << std::endl;
}

///Handle functions:
void CowFarm::handleCowFarm(Farm *farm) {}//do nothing
void CowFarm::handleSheepFarm(Farm *farm) { farm->CowFarmWantsToHaveMe(this); }
void CowFarm::handleChickenFarm(Farm *farm) {}//do nothing

///Want me functions:
void CowFarm::CowFarmWantsToHaveMe(Farm *farm) {}//do nothing
void CowFarm::SheepFarmWantsToHaveMe(Farm *farm) {}//do nothing
void CowFarm::ChickenFarmWantsToHaveMe(Farm *farm) { farm->addClient(this); }

void CowFarm::addClient(Farm *farm) {
    Farm::addClient(farm);
    std::cout << "Cow farm(" << this->getFarmID() << ") Added Sheep farm(" <<
              farm->getFarmID() << ") to his client list" << std::endl;
}

void CowFarm::BuyAnimals() {
    int count = 0;
    int current_amount = this->getFarmMoney();
    while (current_amount >= Cow::getPrice()) {
        Animal *new_cow = new Cow();
        this->reduceMoneyFromFarm(Cow::getPrice());
        this->addAnimalToFarm(new_cow);
        current_amount -= Cow::getPrice();
        count++;
    }
    if (count > 0) {
        std::cout << "Cow farm(" << this->getFarmID() << ") bought " << count << " cows for "
                  << count * Cow::getPrice()
                  << " dollars"
                  << std::endl;
    }
}


void CowFarm::trade() {
    int count = 0;
    for (int i = 0; i < this->getNumberOfClients(); ++i) {
        while (this->getNumOfProducts_Produced() > 0 && this->MyClients[i]->getFarmMoney() >= MilkCost) {

            this->addMoneyToFarm(MilkCost);
            this->MyClients[i]->reduceMoneyFromFarm(MilkCost);
            ///updating the counters:
            this->removeProducts_Produced(1);
            this->MyClients[i]->addProducts_Desired(1);

            count++;
        }
        if (count > 0) {
            std::cout << "Sheep farm(" << this->MyClients[i]->getFarmID() << ") bought " << count << " milk for " <<
                      count * MilkCost << " dollars from Cow farm(" << this->getFarmID() << ")" << std::endl;
            count = 0;
        }
    }
}

