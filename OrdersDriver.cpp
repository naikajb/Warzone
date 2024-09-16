#include "Orders.h"
#include <iostream>

// Test function to demonstrate various scenarios
void testOrdersList() {
    OrdersList list;
    
    // Adding orders to the list
    list.addOrder(std::make_unique<DeployOrder>());
    list.addOrder(std::make_unique<AdvanceOrder>());
    list.addOrder(std::make_unique<BombOrder>());
    list.addOrder(std::make_unique<BlockadeOrder>());
    list.addOrder(std::make_unique<AirliftOrder>());
    list.addOrder(std::make_unique<NegotiateOrder>());

    std::cout << "Initial OrdersList:\n" << list << std::endl;

    std::cout << "Executing orders:\n";
    for (size_t i = 0; i < 6; ++i) {
        list.getOrder(i)->executeOrder();
    }
    std::cout << std::endl;

    std::cout << "Before Validation:\n";
    for (size_t i = 0; i < 6; ++i) {
    std::cout << *list.getOrder(i) << std::endl;
    }
    std::cout << std::endl;


    // Move the second order to the last position
    list.moveOrder(1, 5);

    std::cout << "After moving the second order to the last position:\n" << list << std::endl;

    // Remove the first order
    list.removeOrder(0);

    std::cout << "After removing the first order:\n" << list << std::endl;

    // Demonstrate orders before execution and validation
    std::cout << "Testing specific cases:\n";

    std::cout << "Testing DeployOrder:\n";
    auto deployOrder = std::make_unique<DeployOrder>();
    std::cout << "Validating DeployOrder: " << deployOrder->validateOrder() << std::endl;
    std::cout << "Executing DeployOrder:\n";
    deployOrder->executeOrder();
    std::cout << *deployOrder << std::endl;

    std::cout << "Testing AdvanceOrder:\n";
    auto advanceOrder = std::make_unique<AdvanceOrder>();
    std::cout << "Validating AdvanceOrder: " << advanceOrder->validateOrder() << std::endl;
    std::cout << "Executing AdvanceOrder:\n";
    advanceOrder->executeOrder();
    std::cout << *advanceOrder << std::endl;
}

int main() {
    testOrdersList();
    return 0;
}
