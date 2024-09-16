#include "Orders.h"
#include <iostream>
#include <memory>

void testOrdersLists() {
    // Create an OrdersList instance
    OrdersList ordersList;

    // Create instances of each order type and add them to the OrdersList
    ordersList.addOrder(std::make_unique<DeployOrder>());
    ordersList.addOrder(std::make_unique<AdvanceOrder>());
    ordersList.addOrder(std::make_unique<BombOrder>());
    ordersList.addOrder(std::make_unique<BlockadeOrder>());
    ordersList.addOrder(std::make_unique<AirliftOrder>());
    ordersList.addOrder(std::make_unique<NegotiateOrder>());

    // Print the initial state of the OrdersList
    std::cout << "Initial OrdersList:" << std::endl;
    std::cout << ordersList << std::endl;

    // Validate and execute orders
    std::cout << "Executing orders:" << std::endl;
    for (size_t i = 0; i < 6; ++i) {
        // Get a copy of the order at index i
        std::unique_ptr<Order> order = ordersList.getOrder(static_cast<int>(i));
        
        // Validate and execute the order
        if (order) {
            if (order->validateOrder()) {
                order->executeOrder();
                std::cout << *order << std::endl;
            } else {
                std::cout << "Order at index " << i << " is invalid and cannot be executed." << std::endl;
            }
        } else {
            std::cout << "Order at index " << i << " does not exist." << std::endl;
        }
    }

    // Move the second order to the last position
    ordersList.moveOrder(1, 5);
    std::cout << "After moving the second order to the last position:" << std::endl;
    std::cout << ordersList << std::endl;

    // Remove the first order
    ordersList.removeOrder(0);
    std::cout << "After removing the first order:" << std::endl;
    std::cout << ordersList << std::endl;
}

int main() {
    // Run the test function
    testOrdersLists();
    return 0;
}
