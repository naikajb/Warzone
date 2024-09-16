#include "Orders.h"

// Base class Order implementation
Order::Order() : isExecuted(false), OrderDescription("Order is undefined"), OrderEffect("None") {}

Order::~Order() {}

std::ostream& operator<<(std::ostream& out, const Order& order) {
    out << "Order Description: " << order.OrderDescription;
    if (order.isExecuted) {
        out << " | Order Effect: " << order.OrderEffect;
    }
    return out;
}

// Copy constructor and assignment operator for Order
Order::Order(const Order& other)
    : OrderDescription(other.OrderDescription),
      OrderEffect(other.OrderEffect),
      isExecuted(other.isExecuted) {}

Order& Order::operator=(const Order& other) {
    if (this != &other) {
        OrderDescription = other.OrderDescription;
        OrderEffect = other.OrderEffect;
        isExecuted = other.isExecuted;
    }
    return *this;
}

// DeployOrder class implementation
DeployOrder::DeployOrder() {
    OrderDescription = "Deploy Order";
}

DeployOrder::~DeployOrder() {}

bool DeployOrder::validateOrder() const {
    return true; // Placeholder for actual validation
}

void DeployOrder::executeOrder() {
    if (validateOrder()) {
        isExecuted = true;
        OrderEffect = "Armies have been deployed";
    }
}

std::unique_ptr<Order> DeployOrder::clone() const {
    return std::make_unique<DeployOrder>(*this);
}

// AdvanceOrder class implementation
AdvanceOrder::AdvanceOrder() {
    OrderDescription = "Advance Order";
}

AdvanceOrder::~AdvanceOrder() {}

bool AdvanceOrder::validateOrder() const {
    return true; // Placeholder for actual validation
}

void AdvanceOrder::executeOrder() {
    if (validateOrder()) {
        isExecuted = true;
        OrderEffect = "Armies have advanced";
    }
}

std::unique_ptr<Order> AdvanceOrder::clone() const {
    return std::make_unique<AdvanceOrder>(*this);
}

// BombOrder class implementation
BombOrder::BombOrder() {
    OrderDescription = "Bomb Order";
}

BombOrder::~BombOrder() {}

bool BombOrder::validateOrder() const {
    return true; // Placeholder for actual validation
}

void BombOrder::executeOrder() {
    if (validateOrder()) {
        isExecuted = true;
        OrderEffect = "Territory has been bombed";
    }
}

std::unique_ptr<Order> BombOrder::clone() const {
    return std::make_unique<BombOrder>(*this);
}

// BlockadeOrder class implementation
BlockadeOrder::BlockadeOrder() {
    OrderDescription = "Blockade Order";
}

BlockadeOrder::~BlockadeOrder() {}

bool BlockadeOrder::validateOrder() const {
    return true; // Placeholder for actual validation
}

void BlockadeOrder::executeOrder() {
    if (validateOrder()) {
        isExecuted = true;
        OrderEffect = "Territory has been blockaded";
    }
}

std::unique_ptr<Order> BlockadeOrder::clone() const {
    return std::make_unique<BlockadeOrder>(*this);
}

// AirliftOrder class implementation
AirliftOrder::AirliftOrder() {
    OrderDescription = "Airlift Order";
}

AirliftOrder::~AirliftOrder() {}

bool AirliftOrder::validateOrder() const {
    return true; // Placeholder for actual validation
}

void AirliftOrder::executeOrder() {
    if (validateOrder()) {
        isExecuted = true;
        OrderEffect = "Armies have been airlifted";
    }
}

std::unique_ptr<Order> AirliftOrder::clone() const {
    return std::make_unique<AirliftOrder>(*this);
}

// NegotiateOrder class implementation
NegotiateOrder::NegotiateOrder() {
    OrderDescription = "Negotiate Order";
}

NegotiateOrder::~NegotiateOrder() {}

bool NegotiateOrder::validateOrder() const {
    return true; // Placeholder for actual validation
}

void NegotiateOrder::executeOrder() {
    if (validateOrder()) {
        isExecuted = true;
        OrderEffect = "A truce has been negotiated";
    }
}

std::unique_ptr<Order> NegotiateOrder::clone() const {
    return std::make_unique<NegotiateOrder>(*this);
}

// OrdersList class implementation
OrdersList::OrdersList() {}

OrdersList::~OrdersList() {
    // Unique pointers manage memory automatically
}

void OrdersList::addOrder(std::unique_ptr<Order> order) {
    orders.push_back(std::move(order));
}

void OrdersList::moveOrder(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        std::swap(orders[fromIndex], orders[toIndex]);
    }
}

void OrdersList::removeOrder(int index) {
    if (index >= 0 && index < orders.size()) {
        orders.erase(orders.begin() + index);
    }
}

std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList) {
    for (const auto& order : ordersList.orders) {
        out << *order << std::endl;
    }
    return out;
}

// Copy constructor for OrdersList
OrdersList::OrdersList(const OrdersList& other) {
    for (const auto& order : other.orders) {
        orders.push_back(order->clone());
    }
}

// Assignment operator for OrdersList
OrdersList& OrdersList::operator=(const OrdersList& other) {
    if (this != &other) {
        orders.clear();
        for (const auto& order : other.orders) {
            orders.push_back(order->clone());
        }
    }
    return *this;
}
