//
// Created by ise on 12/31/21.
//

#include "Farm.h"

int Farm::ID=0;

Farm::Farm() {
    ID++;
    FarmID = ID;
    Money=0;
    Products_Desired=0;
    Products_Produced=0;
    Animals;
    MyClients;
}

Farm::~Farm() {
    for (int i = 0; i < this->Animals.size(); ++i) {
        delete this->Animals[i];
    }
    Animals.clear();

//    for (int i = 0; i < this->MyClients.size(); ++i) {
//        delete this->MyClients[i];
//    }
    MyClients.clear();
}

int Farm::getFarmID() const {
    return this->FarmID;
}

int Farm::getFarmMoney() const {
    return this->Money;
}

void Farm::addMoneyToFarm(int amount) {
    this->Money+=amount;
}

void Farm::reduceMoneyFromFarm(int amount) {
    this->Money-=amount;
}

int Farm::getNumberOfAnimalsInFarm() const {
    return (int)this->Animals.size();
}

int Farm::getNumOfProducts_Desired() const {
    return this->Products_Desired;
}

int Farm::getNumOfProducts_Produced() const {
    return this->Products_Produced;
}

void Farm::addProducts_Desired(int amount) {
    this->Products_Desired+=amount;
}

void Farm::addProducts_Produced(int amount) {
    this->Products_Produced+=amount;
}

void Farm::removeProducts_Produced(int amount) {
    this->Products_Produced-=amount;
}

void Farm::addClient(Farm *farm) {
    this->MyClients.push_back(farm);
}

void Farm::getFarmYield() {
    int yield =0;
    for (int i = 0; i < this->Animals.size(); ++i) {
        yield+=Animals[i]->getAnimalAge();
    }
    this->addProducts_Produced(yield);
}

void Farm::addAnimalToFarm(Animal *animal) {
    this->Animals.push_back(animal);
}

void Farm::increaseAnimalsFarmAge() {
    for (int i = 0; i < this->Animals.size(); ++i) {
        this->Animals[i]->increaseAgeByValue(1);
    }
}

int Farm::getNumberOfClients() {
    return this->MyClients.size();
}

void Farm::Slaughter() {
    for (int i = 0; i < this->Animals.size(); ++i) {
        if (this->Animals[i]->getAnimalAge() >= this->Animals[i]->getAnimalMaxAge()) {
            delete this->Animals[i];
            this->Animals.erase(this->Animals.begin()+i);
            i--;
        }
    }
}