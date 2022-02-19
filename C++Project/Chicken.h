//
// Created by ise on 12/31/21.
//

#ifndef CPP_PROJECT_CHICKEN_H
#define CPP_PROJECT_CHICKEN_H
#include "Animal.h"

class Chicken : public Animal{
private:
    static int price;
    const static int maxAge =3;
public:
    Chicken();
    ~Chicken() override=default;
    static int getPrice();
    int getAnimalMaxAge(){return maxAge;};
};


#endif //CPP_PROJECT_CHICKEN_H
