#include <iostream>

// Include headers for each part's test function
#include "OrdersDriver.h"
#include "GameEngine.h"

int main(){
    std::cout << "Testing Part 3 - Orders List Component :" << std::endl;

    // Call funcion to test the Orders list
    testOrdersLists();
    testGameStates();

    return 0;
}