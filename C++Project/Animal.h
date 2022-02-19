//
// Created by ise on 12/31/21.
//

#ifndef CPP_PROJECT_ANIMAL_H
#define CPP_PROJECT_ANIMAL_H


class Animal {
private:
    int Age;
    int MaxAge;
public:
    ///Default constructor:
    Animal(){Age=0,  MaxAge=0;}; //Price =0,
    ///Destructor:
    virtual ~Animal(){};

    ///Age getter&setter:
    int getAnimalAge() const{return Age;};
    void increaseAgeByValue(int increase);

    ///MaxAge getter&setter:
    int getAnimalMaxAge(){return MaxAge;};
    void setAnimalMaxAge(int updated_maxAge);
};


#endif //CPP_PROJECT_ANIMAL_H
