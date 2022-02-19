//
// Created by ise on 1/6/22.
//

#ifndef CPP_PROJECT_EXCEPTIONS_H
#define CPP_PROJECT_EXCEPTIONS_H
#include <exception>

class CowFarmException: public std::exception{
public:
    virtual const char* what() const throw(){
        return "Insert valid number of cow farms";
    }
};

class SheepFarmException: public std::exception{
public:
    virtual const char* what() const throw(){
        return "Insert valid number of sheep farms";
    }
};

class ChickenFarmException: public std::exception{
public:
    virtual const char* what() const throw(){
        return "Insert valid number of chicken farms";
    }
};
#endif //CPP_PROJECT_EXCEPTIONS_H
