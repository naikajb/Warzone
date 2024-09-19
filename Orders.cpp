#include "Orders.h"
#include <iostream>
#include <algorithm>

// Base class order implementation
Order::Order() : orderDescription("undefined"), orderEffect("none"), executed(false) {}

//Destructor
Order::~Order() {}

//Assignment operator
Order& Order::operator = (const Order& original){
    if(this != &original){
        this->orderDescription = original.orderDescription;
        this->orderEffect = original.orderEffect;
        this->executed = original.executed;
    }
    return *this;
}

//Overloaded stream isnertion operator
std::ostream& operator<<(std::ostream& outputStream, const Order& order) {
    outputStream << "The order: " << order.orderDescription;
    if (order.executed) {
        outputStream << " ~~~ The effect: " << order.orderEffect;
    }
    return outputStream;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Deploy Order - derived class Deploy implementation
Deploy::Deploy() {
    orderDescription = "Deploy order - place armies on a territory";
}
Deploy::~Deploy() {}

bool Deploy::validateOrder() {
    return true;
}

void Deploy::executeOrder() {
    executed = true;
    orderEffect = "Armies have been deployed.";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Advance Order
Advance::Advance() {
    orderDescription = "Advance Order - move armies to an adjacent territory";
}
Advance::~Advance() {}
bool Advance::validateOrder() {
    // Placeholder logic for validation
    return true;
}
void Advance::executeOrder() {
    executed = true;
    orderEffect = "Armies have advanced.";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Bomb Order
Bomb::Bomb() {
    orderDescription = "Bomb Order - bomb a territory to weaken its defense";
}
Bomb::~Bomb() {}
bool Bomb::validateOrder() {
    // Placeholder logic for validation
    return true;
}
void Bomb::executeOrder() {
    executed = true;
    orderEffect = "Territory has been bombed.";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Blockade Order
Blockade::Blockade() {
    orderDescription = "Blockade Order - blockade a territory to prevent movement";
}
Blockade::~Blockade() {}
bool Blockade::validateOrder() {
    // Placeholder logic for validation
    return true;
}
void Blockade::executeOrder() {
    executed = true;
    orderEffect = "Territory has been blockaded.";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Airlift Order
Airlift::Airlift() {
    orderDescription = "Airlift Order - move armies from one territory to another by air";
}
Airlift::~Airlift() {}
bool Airlift::validateOrder() {
    // Placeholder logic for validation
    return true;
}
void Airlift::executeOrder() {
    executed = true;
    orderEffect = "Armies have been airlifted";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Negotiate Order
Negotiate::Negotiate() {
    orderDescription = "Negotiate Order - negotiate a truce with another player";
}
Negotiate::~Negotiate() {}
bool Negotiate::validateOrder() {
    // Placeholder logic for validation
    return true;
}
void Negotiate::executeOrder() {
    executed = true;
    orderEffect = "Truce has been negotiated.";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// OrdersList class implementation
OrdersList::OrdersList() {}
OrdersList::~OrdersList() {
    for (Order* order : orders) {
        delete order;
    }
}

void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
}

void OrdersList::move(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        std::swap(orders[fromIndex], orders[toIndex]);
    }
}

void OrdersList::remove(int index) {
    if (index >= 0 && index < orders.size()) {
        delete orders[index];
        orders.erase(orders.begin() + index);
    }
}

std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList) {
    for (size_t i = 0; i < ordersList.orders.size(); ++i) {
        out << *ordersList.orders[i] << std::endl;
    }
    return out;
}
