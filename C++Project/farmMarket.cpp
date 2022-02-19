//============================================================================
// Name        : farmMarket.cpp
// Author      : OMER HANAN
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Market.h"



int main() {

    Market* market = new Market();
    char gameOption='1';
    while(gameOption!='4')
    {
        cout<< "Year:" << market->getYear() <<endl;
        cout<< "1. Next year" << endl;
        cout<< "2. Fast forward" << endl;
        cout<< "3. Print farms in market" << endl;
        cout<< "4. Exit" << endl;
        cin >> gameOption;
        switch(gameOption){
            case '1':
                market->nextYear();
                break;
            case '2':
                market->fastForwardYears();
                break;
            case '3':
                market->printMarketFarms();
                break;
            case '4':
                cout<<"Bye.. "<<endl;
                delete market;
                break;
        }
    }

    return 0;
}