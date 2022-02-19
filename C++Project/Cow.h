//
// Created by ise on 12/31/21.
//

#ifndef CPP_PROJECT_COW_H
#define CPP_PROJECT_COW_H
#include "Animal.h"

class Cow: public Animal{
private:
    static int price;

public:
    Cow();
    ~Cow() override= default;
    static int getPrice();
};


#endif //CPP_PROJECT_COW_H
