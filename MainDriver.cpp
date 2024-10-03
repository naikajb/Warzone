#include <iostream>

// Include headers for each part's test function
#include "OrdersDriver.h"
#include "MapDriver.h"
#include "GameEngine.h"
#include "CardDriver.h"

int main(){

    std::cout << "Testing Part 1 - Map Component :" << std::endl;

    // Call funcion to test the Map(s)
    testLoadMaps();

    std::cout << "Testing Part 3 - Orders List Component :" << std::endl;

    // Call funcion to test the Orders list
    testOrdersLists();

    std::cout << "Testing Part 4 - Cards Component :" << std::endl;

    // Call funcion to test the Cards
    testCards();

    std::cout << "Testing Part 5 - Game Engine Component :" << std::endl;

    testGameStates();

    return 0;
}