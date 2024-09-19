#include "Orders.h"
#include <iostream>

void testOrdersLists() {
    OrdersList ordersList;

    // Create different orders
    Order* deploy = new Deploy();
    Order* advance = new Advance();
    Order* bomb = new Bomb();
    Order* blockade = new Blockade();
    Order* airlift = new Airlift();
    Order* negotiate = new Negotiate();

    // Add orders to the list
    ordersList.addOrder(deploy);
    ordersList.addOrder(advance);
    ordersList.addOrder(bomb);
    ordersList.addOrder(blockade);
    ordersList.addOrder(airlift);
    ordersList.addOrder(negotiate);

    // Print initial list
    std::cout << "Initial Orders List:" << std::endl;
    std::cout << ordersList << std::endl;

    // Move orders
    ordersList.move(0, 5);  // Move the first order to the end
    std::cout << "After Moving Deploy to Last:" << std::endl;
    std::cout << ordersList << std::endl;

    // Remove an order
    ordersList.remove(2);  // Remove Bomb order
    std::cout << "After Removing Bomb Order:" << std::endl;
    std::cout << ordersList << std::endl;

    // Execute some orders
    deploy->executeOrder();
    advance->executeOrder();

    std::cout << "After Executing Deploy and Advance Orders:" << std::endl;
    std::cout << ordersList << std::endl;
}

int main() {
    testOrdersLists();
    return 0;
}
