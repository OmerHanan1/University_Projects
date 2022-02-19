//
// Created by ise on 1/1/22.
//
#include <iostream>
#include "Farm.h"
#include "CowFarm.h"
#include "SheepFarm.h"
#include "ChickenFarm.h"
#include "Market.h"
#include "Exceptions.h"

Market::Market() {
    year=0;
}

int Market::getYear() const {
    return this->year;
}

void Market::printMarketFarms() {
    std::cout<<"----Market Farms----"<<std::endl;
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        MarketFarms[i]->PrintFarm();
    }
}

void Market::EstablishmentOfNewFarms() {
    int cow, sheep, chicken;

    std::cout<<"----Creating new farms----"<<std::endl;
    bool flag = true;
    while(flag){
        try {
            std::cout<<"How many new cow farms will be added this year?"<<std::endl;
            std::cin>>cow;
            if(cow < 0){
                throw CowFarmException();
            }
            std::cout<<"How many new sheep farms will be added this year?"<<std::endl;
            std::cin>>sheep;
            if(sheep < 0){
                throw SheepFarmException();
            }
            std::cout<<"How many new chicken farms will be added this year?"<<std::endl;
            std::cin>>chicken;
            if(chicken < 0){
                throw ChickenFarmException();
            }
            flag = false;
        }


        catch (std::exception& e){
            std::cout<<e.what()<<std::endl;
        }
    }



    std::cout<<"----Adding new farms to market----"<<std::endl;
    if (cow>0){
        for (int i = 0; i < cow; ++i) {
            Farm* cow_farm = new CowFarm();
            for (int j = 0; j < this->MarketFarms.size(); ++j) {
                ///add farms to new farm client list:
                cow_farm->handleCowFarm(this->MarketFarms[j]);
                cow_farm->handleSheepFarm(this->MarketFarms[j]);
                cow_farm->handleChickenFarm(this->MarketFarms[j]);
                ///add new farm to exist farms clients lists:
                this->MarketFarms[j]->handleCowFarm(cow_farm);
                this->MarketFarms[j]->handleSheepFarm(cow_farm);
                this->MarketFarms[j]->handleChickenFarm(cow_farm);
            }
            this->MarketFarms.push_back(cow_farm);
        }
    }
    if (sheep>0){
        for (int i = 0; i < sheep; ++i) {
            Farm* sheep_farm = new SheepFarm();
            for (int j = 0; j < this->MarketFarms.size(); ++j) {
                ///add farms to new farm client list:
                sheep_farm->handleCowFarm(this->MarketFarms[j]);
                sheep_farm->handleSheepFarm(this->MarketFarms[j]);
                sheep_farm->handleChickenFarm(this->MarketFarms[j]);
                ///add new farm to exist farms clients lists:
                this->MarketFarms[j]->handleCowFarm(sheep_farm);
                this->MarketFarms[j]->handleSheepFarm(sheep_farm);
                this->MarketFarms[j]->handleChickenFarm(sheep_farm);
            }
            this->MarketFarms.push_back(sheep_farm);
        }
    }
    if (chicken>0){
        for (int i = 0; i < chicken; ++i) {
            Farm* chicken_farm = new ChickenFarm();
            for (int j = 0; j < this->MarketFarms.size(); ++j) {
                ///add farms to new farm client list:
                chicken_farm->handleCowFarm(this->MarketFarms[j]);
                chicken_farm->handleSheepFarm(this->MarketFarms[j]);
                chicken_farm->handleChickenFarm(this->MarketFarms[j]);
                ///add new farm to exist farms clients lists:
                this->MarketFarms[j]->handleCowFarm(chicken_farm);
                this->MarketFarms[j]->handleSheepFarm(chicken_farm);
                this->MarketFarms[j]->handleChickenFarm(chicken_farm);
            }
            this->MarketFarms.push_back(chicken_farm);
        }
    }
}

void Market::TradeDay() {
    std::cout<<"----Begin Market----"<<std::endl;
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        //for each market clients do trade.
        this->MarketFarms[i]->trade();
    }
}

void Market::BuyAnimal() {
    std::cout<<"----Buy Animals----"<<std::endl;
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        this->MarketFarms[i]->BuyAnimals();
    }
}

void Market::harvestAllFarms() {
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        this->MarketFarms[i]->getFarmYield();
    }
}

void Market::passYear() {
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        this->MarketFarms[i]->addMoneyToFarm(10);
        this->MarketFarms[i]->increaseAnimalsFarmAge();
    }
}

void Market::Slaughtering() {
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        this->MarketFarms[i]->Slaughter();
    }
}


void Market::nextYear() {
    ///creating new farms:
    this->EstablishmentOfNewFarms();
    ///farms harvest:
    this->harvestAllFarms();
    ///trade day:
    this->TradeDay();
    this->BuyAnimal();
    ///add money not related:
    this->passYear();
    ///kill the old animals:
    this->Slaughtering();

    this->year++;
}

void Market::fastForwardYears() {
    int years;
    std::cout<<"How many years to fast forward?"<<std::endl;
    std::cin>>years;

    for (int i = 0; i < years; ++i) {
        this->harvestAllFarms();
        this->TradeDay();
        this->BuyAnimal();
        this->passYear();
        this->Slaughtering();
        this->year++;
    }
}

Market::~Market() {
    for (int i = 0; i < this->MarketFarms.size(); ++i) {
        delete this->MarketFarms[i];
    }
    this->MarketFarms.clear();
}