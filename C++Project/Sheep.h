//
// Created by ise on 12/31/21.
//

#ifndef CPP_PROJECT_SHEEP_H
#define CPP_PROJECT_SHEEP_H
#include "Animal.h"

class Sheep: public Animal{
private:
    static int price;

public:
    Sheep();
    ~Sheep() override= default;
    static int getPrice();
};


#endif //CPP_PROJECT_SHEEP_H
