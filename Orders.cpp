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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DeployOrder::DeployOrder(){
    OrderDescription = "Deploy Order";
}

DeployOrder::~DeployOrder() {}

bool DeployOrder::validateOrder() const{
    return true;
}

void DeployOrder::executeOrder(){
    if(validateOrder()){
        isExecuted = true;
        OrderEffect = "Armies are deployed";
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AdvanceOrder::AdvanceOrder(){
    OrderDescription = "Advance Order";
}

AdvanceOrder::~AdvanceOrder() {}

bool AdvanceOrder::validateOrder() const{
    return true;
}

void AdvanceOrder::executeOrder(){
    if(validateOrder()){
        isExecuted = true;
        OrderEffect = "Armies have advanced";
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BombOrder::BombOrder(){
    OrderDescription = "Bomb Order";
}

BombOrder::~BombOrder() {}

bool BombOrder::validateOrder() const{
    return true;
}

void BombOrder::executeOrder(){
    if(validateOrder()){
        isExecuted = true;
        OrderEffect = "Territory has been bombed";
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BlockadeOrder::BlockadeOrder(){
    OrderDescription = "Blockade Order";
}

BlockadeOrder::~BlockadeOrder() {}

bool BlockadeOrder::validateOrder() const{
    return true;
}

void BlockadeOrder::executeOrder(){
    if(validateOrder()){
        isExecuted = true;
        OrderEffect = "Territory has been blockaded";
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
AirliftOrder::AirliftOrder(){
    OrderDescription = "Airlift Order";
}

AirliftOrder::~AirliftOrder() {}

bool AirliftOrder::validateOrder() const{
    return true;
}

void AirliftOrder::executeOrder(){
    if(validateOrder()){
        isExecuted = true;
        OrderEffect = "Armies have been airlifted";
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
NegotiateOrder::NegotiateOrder(){
    OrderDescription = "Negotiate Order";
}

NegotiateOrder::~NegotiateOrder() {}

bool NegotiateOrder::validateOrder() const{
    return true;
}

void NegotiateOrder::executeOrder(){
    if(validateOrder()){
        isExecuted = true;
        OrderEffect = "A truce has been negotiated";
    }
}



