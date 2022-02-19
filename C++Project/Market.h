//
// Created by ise on 1/1/22.
//

#ifndef CPP_PROJECT_MARKET_H
#define CPP_PROJECT_MARKET_H
#include <vector>
#include "Farm.h"
#include <iostream>
using namespace std;

class Market {
private:
    int year;
    std::vector<Farm*> MarketFarms;
public:
    Market();
    void EstablishmentOfNewFarms();
    void TradeDay();
    int getYear() const;
    void nextYear();
    void fastForwardYears();
    void printMarketFarms();
    void BuyAnimal();
    void harvestAllFarms();
    void passYear();
    void Slaughtering();
    ~Market();
};


#endif //CPP_PROJECT_MARKET_H
