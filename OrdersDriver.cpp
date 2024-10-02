#include "Orders.h"
#include <iostream>

// Function to test the functuonality of the OrdersList class
void testOrdersLists() {

    // Create an instance of OrdersList to manage orders
    OrdersList ordersList;

    // Create different TYPES of orders 
    Order* deploy = new Deploy();
    Order* advance = new Advance();
    Order* bomb = new Bomb();
    Order* blockade = new Blockade();
    Order* airlift = new Airlift();
    Order* negotiate = new Negotiate();

    // Add created orders to the orders list
    ordersList.addOrder(deploy);
    ordersList.addOrder(advance);
    ordersList.addOrder(bomb);
    ordersList.addOrder(blockade);
    ordersList.addOrder(airlift);
    ordersList.addOrder(negotiate);

    // Print the initial list of orders
    std::cout << "Initial Orders List:" << std::endl;
    std::cout << ordersList << std::endl;

    // Move the 1rst order (deploy) to the end of the list
    ordersList.move(0, 5);  // Move the first order to the end
    std::cout << "After Moving Deploy to Last:" << std::endl;
    std::cout << ordersList << std::endl;

    // Remove an order from the orders list
    ordersList.remove(2);  // Remove Bomb order
    std::cout << "After Removing Bomb Order:" << std::endl;
    std::cout << ordersList << std::endl;

    // Execute the 'deploy' and the 'advance' orders to change their state
    deploy->executeOrder();
    advance->executeOrder();

    // Print the orders list after executing 'deploy' order and 'advance' order
    std::cout << "After Executing Deploy and Advance Orders:" << std::endl;
    std::cout << ordersList << std::endl;
}

// Main function to run the test
int main_OrdersDriver() {
    testOrdersLists(); //Call the function to test OrdersList functionality
    return 0;
}
