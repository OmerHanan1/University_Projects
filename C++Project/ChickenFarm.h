//
// Created by ise on 12/31/21.
//

#ifndef CPP_PROJECT_CHICKENFARM_H
#define CPP_PROJECT_CHICKENFARM_H
#include <iostream>
#include "Farm.h"

class ChickenFarm: public Farm{
public:
    ChickenFarm();
    virtual ~ChickenFarm(){ };
    void PrintFarm() override;

    void handleCowFarm(Farm *farm) override;
    void handleSheepFarm(Farm *farm) override;
    void handleChickenFarm(Farm *farm) override;

    void CowFarmWantsToHaveMe(Farm *farm) override;
    void SheepFarmWantsToHaveMe(Farm *farm) override;
    void ChickenFarmWantsToHaveMe(Farm *farm) override;

    void addClient(Farm *farm) override;
    void BuyAnimals() override;
    void trade() override;
};


#endif //CPP_PROJECT_CHICKENFARM_H
