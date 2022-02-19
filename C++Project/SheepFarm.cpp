//
// Created by ise on 12/31/21.
//

#include "SheepFarm.h"
#include "Sheep.h"
#include "Costs.h"

SheepFarm::SheepFarm() {

    ///each farm starts the game with 10 dollars:
    this->addMoneyToFarm(10);

    ///each farm starts the game with 3 animals:
    for (int i = 0; i < 3; ++i) {
        Animal *cow = new Sheep();
        this->addAnimalToFarm(cow);
    }
}

void SheepFarm::PrintFarm() {
    std::cout << "Farm Id: " << this->getFarmID() << ", type: Sheep farm, Money: " <<
              this->getFarmMoney() << ", Animals: " << this->getNumberOfAnimalsInFarm() << " sheep, Products: " <<
              "Milk[" << this->getNumOfProducts_Desired() << "], Wool[" << this->getNumOfProducts_Produced()
              << "], Eggs[0]" << std::endl;
}

///Handle functions:
void SheepFarm::handleCowFarm(Farm *farm) {}//do nothing
void SheepFarm::handleSheepFarm(Farm *farm) {}//do nothing
void SheepFarm::handleChickenFarm(Farm *farm) { farm->SheepFarmWantsToHaveMe(this); }//do nothing

///Want me functions:
void SheepFarm::CowFarmWantsToHaveMe(Farm *farm) { farm->addClient(this); }//do nothing
void SheepFarm::SheepFarmWantsToHaveMe(Farm *farm) {}//do nothing
void SheepFarm::ChickenFarmWantsToHaveMe(Farm *farm) {}//do nothing

void SheepFarm::addClient(Farm *farm) {
    Farm::addClient(farm);
    std::cout << "Sheep farm(" << this->getFarmID() << ") Added Chicken farm(" <<
              farm->getFarmID() << ") to his client list" << std::endl;
}

void SheepFarm::BuyAnimals() {
    int count = 0;
    int current_amount = this->getFarmMoney();
    while (current_amount >= Sheep::getPrice()) {
        Animal *new_sheep = new Sheep();
        this->reduceMoneyFromFarm(Sheep::getPrice());
        this->addAnimalToFarm(new_sheep);
        current_amount -= Sheep::getPrice();
        count++;
    }
    if (count > 0) {
        std::cout << "Sheep farm(" << this->getFarmID() << ") bought " << count << " sheeps for "
                  << count * Sheep::getPrice()
                  << " dollars"
                  << std::endl;
    }
}

void SheepFarm::trade() {
    int count = 0;
    for (int i = 0; i < this->getNumberOfClients(); ++i) {
        while (this->getNumOfProducts_Produced() > 0 && this->MyClients[i]->getFarmMoney() >= WoolCost) {

            this->addMoneyToFarm(WoolCost);
            this->MyClients[i]->reduceMoneyFromFarm(WoolCost);
            ///updating the counters:
            this->removeProducts_Produced(1);
            this->MyClients[i]->addProducts_Desired(1);

            count++;
        }
        if (count > 0) {
            std::cout << "Chicken farm(" << this->MyClients[i]->getFarmID() << ") bought " << count << " wool for " <<
                      count * WoolCost << " dollars from Sheep farm(" << this->getFarmID() << ")" << std::endl;
            count = 0;
        }
    }
}
