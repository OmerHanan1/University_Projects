//
// Created by ise on 12/31/21.
//
#include <vector>
#include "Animal.h"
#ifndef CPP_PROJECT_FARM_H
#define CPP_PROJECT_FARM_H


class Farm {
private:
    static int ID;
    int FarmID;
    int Money;
    int Products_Desired;
    int Products_Produced;

protected:
    std::vector<Animal*> Animals;
    std::vector<Farm*> MyClients;

public:
    ///Default-Constructor:
    Farm();

    ///ID get:
    int getFarmID() const;

    ///Money getter&setters:
    int getFarmMoney() const;
    void addMoneyToFarm(int amount);
    void reduceMoneyFromFarm(int amount);

    ///Products getter&setters:
    int getNumOfProducts_Desired() const;
    int getNumOfProducts_Produced() const;
    void addProducts_Desired(int amount);
    void addProducts_Produced(int amount);
    void removeProducts_Produced(int amount);

    ///Animals getter&setters:
    int getNumberOfAnimalsInFarm() const;
    void addAnimalToFarm(Animal* animal);
    void increaseAnimalsFarmAge();
    void Slaughter();

    ///Farm yield:
    virtual void getFarmYield();

    ///Handle new optional clients:
    virtual void handleCowFarm(Farm* farm)=0;
    virtual void handleSheepFarm(Farm* farm)=0;
    virtual void handleChickenFarm(Farm* farm)=0;

    ///Farms want to have me as client:
    virtual void CowFarmWantsToHaveMe(Farm* farm)=0;
    virtual void SheepFarmWantsToHaveMe(Farm* farm)=0;
    virtual void ChickenFarmWantsToHaveMe(Farm* farm)=0;

    ///AddClient:
    virtual void addClient(Farm* farm)=0;
    int getNumberOfClients();
    virtual void trade()=0;

    ///add animal:
    virtual void BuyAnimals()=0;

    ///Print farm:
    virtual void PrintFarm()=0;

    ///Destructor:
    virtual ~Farm();
};


#endif //CPP_PROJECT_FARM_H
