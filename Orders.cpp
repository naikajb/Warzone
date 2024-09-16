#include "Orders.h"
#include <iostream>
#include <vector>
#include <algorithm>

Order::Order() : isExecuted(false), OrderDescription("order is undefined"), OrderEffect("none") {}

Order::~Order() {}

std::ostream& operator<<(std::ostream& out, const Order& order){
    out << "The order is: " << order.OrderDescription;
    if (order.isExecuted){
        out << " | The effect is: " << order.OrderEffect;
    }
    return out;
}