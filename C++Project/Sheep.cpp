//
// Created by ise on 12/31/21.
//

#include "Sheep.h"

int Sheep::price =5;

Sheep::Sheep() {
    Animal::setAnimalMaxAge(5);
}

int Sheep::getPrice() {
    return Sheep::price;
}