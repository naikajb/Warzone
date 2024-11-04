#include "Orders.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Base class order implementation
// Default constructor --> initializes an Order with default values
Order::Order() : orderDescription("undefined"), orderEffect("none"), executed(false) {}

//Destructor --> ensure derived class destructors are called properly
Order::~Order() {}

//Assignment operator --> handles deep copying of the order data

//Deep copying is necessary to ensure that each copy of an order has its own distinct memory allocation,
//preventing issues like shared state or accidental modifications to the original order when working with multiple instances

Order& Order::operator = (const Order& original){
    if(this != &original){ //check for self-assignment
        this->orderDescription = original.orderDescription; //copy order description
        this->orderEffect = original.orderEffect; //copy order effect
        this->executed = original.executed; //copy execution status
    }
    return *this;
}

//Overloaded stream isnertion operator for printing order details
std::ostream& operator<<(std::ostream& outputStream, const Order& order) {
    outputStream << "The order: " << order.orderDescription;

    //if the order has been executed, print its effect
    if (order.executed) {
        outputStream << " ~~~ The effect: " << order.orderEffect;
    }
    return outputStream; //return the output stream
}

std::string Order::stringToLog() {
    return orderDescription + " had effect " + orderEffect;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Deploy Order - derived class Deploy implementation

// Constructor sets the order description specific to deploy
Deploy::Deploy() {
    orderDescription = "Deploy order - place armies on a territory";
}
Deploy::~Deploy() {} //destructor

// Validate if the deploy order can be executed 
bool Deploy::validateOrder() {
    return true;
}

// Execute the deploy order and set its effect
void Deploy::executeOrder() {
    executed = true; //mark the order as executed
    orderEffect = "Armies have been deployed."; 
    Notify(this);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Advance Order - derived class 

// Constructor sets the porder description to advance
Advance::Advance() {
    orderDescription = "Advance Order - move armies to an adjacent territory";
}
Advance::~Advance() {} //destructor

// Validate if the advance order can be executed
bool Advance::validateOrder() {
    // Placeholder logic for validation
    return true;
}

// Execute the advance order and set its effect
void Advance::executeOrder() {
    executed = true; 
    orderEffect = "Armies have advanced.";
    Notify(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Bomb Order - derived class

// Constructor sets the order description specific to bomb order
Bomb::Bomb() {
    orderDescription = "Bomb Order - bomb a territory to weaken its defense";
}
Bomb::~Bomb() {} //destructor

// Validate if the bomb order can be executed
bool Bomb::validateOrder() {
    // Placeholder logic for validation
    return true;
}

// Execute the bomb order and set its effect
void Bomb::executeOrder() {
    executed = true;
    orderEffect = "Territory has been bombed.";
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Blockade Order - derived class

// Constructor sets the order description specific to blockade order
Blockade::Blockade() {
    orderDescription = "Blockade Order - blockade a territory to prevent movement";
}
Blockade::~Blockade() {} //destructor

// Validate if the blockade order can be executed 
bool Blockade::validateOrder() {
    // Placeholder logic for validation
    return true;
}

// Execute the bloackade order and set its effect
void Blockade::executeOrder() {
    executed = true;
    orderEffect = "Territory has been blockaded.";
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Airlift Order - derived class

// Constructor sets the order description specific to airlift
Airlift::Airlift() {
    orderDescription = "Airlift Order - move armies from one territory to another by air";
}
Airlift::~Airlift() {} //destructor

// Validate if the airlift order can be executed 
bool Airlift::validateOrder() {
    // Placeholder logic for validation
    return true;
}

// Execute the airlift order and set its effect
void Airlift::executeOrder() {
    executed = true;
    orderEffect = "Armies have been airlifted";
    Notify(this);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Negotiate Order - derived class

// Constructor sets the order description specific to negotiate
Negotiate::Negotiate() {
    orderDescription = "Negotiate Order - negotiate a truce with another player";
}
Negotiate::~Negotiate() {} //destructor

// Validate if the negoatiate order can be executed
bool Negotiate::validateOrder() {
    // Placeholder logic for validation
    return true;
}

// Execute the negotiate order and set its effect
void Negotiate::executeOrder() {
    executed = true;
    orderEffect = "Truce has been negotiated.";
    Notify(this);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// OrdersList class implementation

// Constructor for OrdersList
OrdersList::OrdersList() {}

// Destructor for OrdersList --> ensure all dynamically allocated orders are deleted
OrdersList::~OrdersList() {
    for (Order* order : orders) {
        delete order;
        order = NULL;
    }
}

// Add an order to the list
void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
    Notify(order);
}

// Move an order from one position to another in the list
void OrdersList::move(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        std::swap(orders[fromIndex], orders[toIndex]);
    }
}

// Remove an order from the list by its index
void OrdersList::remove(int index) {
    if (index >= 0 && index < orders.size()) {
        delete orders[index];
        orders.erase(orders.begin() + index);
    }
}

// Overload stream insertion operator for printing the list of orders
std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList) {
    for (size_t i = 0; i < ordersList.orders.size(); ++i) {

        // Print each order using the overloaded << operator
        out << *ordersList.orders[i] << std::endl;
    }
    return out;
}

vector<Order*> OrdersList::getOrders(){
    return orders;
}

std::string OrdersList::stringToLog() {
    std::string logString = "Current Orders List: \n";
    for (Order* order : orders) {
        logString += "\t" + order->stringToLog() + "\n";
    }
    return logString;
}


