#include "Orders.h"

void DeployOrder::executeOrder() {
    std::cout << "Deploy Order executed." << std::endl;
}

bool DeployOrder::validateOrder() {
    return true;
}

std::ostream& DeployOrder::print(std::ostream &out) const {
    out << "Deploy Order Description";
    return out;
}

void AdvanceOrder::executeOrder() {
    std::cout << "Advance Order executed." << std::endl;
}

bool AdvanceOrder::validateOrder() {
    return true;
}

std::ostream& AdvanceOrder::print(std::ostream &out) const {
    out << "Advance Order Description";
    return out;
}

void BombOrder::executeOrder() {
    std::cout << "Bomb Order executed." << std::endl;
}

bool BombOrder::validateOrder() {
    return true;
}

std::ostream& BombOrder::print(std::ostream &out) const {
    out << "Bomb Order Description";
    return out;
}

void BlockadeOrder::executeOrder() {
    std::cout << "Blockade Order executed." << std::endl;
}

bool BlockadeOrder::validateOrder() {
    return true;
}

std::ostream& BlockadeOrder::print(std::ostream &out) const {
    out << "Blockade Order Description";
    return out;
}

void AirliftOrder::executeOrder() {
    std::cout << "Airlift Order executed." << std::endl;
}

bool AirliftOrder::validateOrder() {
    return true;
}

std::ostream& AirliftOrder::print(std::ostream &out) const {
    out << "Airlift Order Description";
    return out;
}

void NegotiateOrder::executeOrder() {
    std::cout << "Negotiate Order executed." << std::endl;
}

bool NegotiateOrder::validateOrder() {
    return true;
}

std::ostream& NegotiateOrder::print(std::ostream &out) const {
    out << "Negotiate Order Description";
    return out;
}

void OrdersList::addOrder(std::unique_ptr<Order> order) {
    orders.push_back(std::move(order));
}

std::unique_ptr<Order>& OrdersList::getOrder(size_t index) {
    return orders[index];
}

void OrdersList::moveOrder(size_t from, size_t to) {
    if (from >= orders.size() || to >= orders.size()) return;
    auto order = std::move(orders[from]);
    orders.erase(orders.begin() + from);
    orders.insert(orders.begin() + to, std::move(order));
}

void OrdersList::removeOrder(size_t index) {
    if (index >= orders.size()) return;
    orders.erase(orders.begin() + index);
}

std::ostream& operator<<(std::ostream &out, const OrdersList &list) {
    for (const auto &order : list.orders) {
        out << *order << std::endl;
    }
    return out;
}


std::ostream& operator<<(std::ostream &out, const Order &order) {
    return order.print(out);
}


