//
// Created by ise on 12/31/21.
//

#include "Cow.h"
int Cow::price = 10;

Cow::Cow() {
    Animal::setAnimalMaxAge(10);
}

int Cow::getPrice() {
    return Cow::price;
}

