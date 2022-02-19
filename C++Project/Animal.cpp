//
// Created by ise on 12/31/21.
//

#include "Animal.h"


void Animal::setAnimalMaxAge(int updated_maxAge) {
    this->MaxAge = updated_maxAge;
}

void Animal::increaseAgeByValue(int increase) {
    this->Age+=increase;
}