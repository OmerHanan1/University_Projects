//
// Created by ise on 12/31/21.
//

#include "Chicken.h"

int Chicken::price=3;

Chicken::Chicken() {
    Animal::setAnimalMaxAge(maxAge);
}

int Chicken::getPrice() {
    return Chicken::price;
}
