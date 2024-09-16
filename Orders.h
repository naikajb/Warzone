#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <memory>
#include <vector>

// Base class
class Order {
public:
    virtual ~Order() = default;  // Declare the destructor once
    virtual void executeOrder() = 0;
    virtual bool validateOrder() = 0;
    virtual std::ostream& print(std::ostream &out) const = 0;
    // Other methods and members
};

std::ostream& operator<<(std::ostream &out, const Order &order);

// Derived classes
class DeployOrder : public Order {
public:
    void executeOrder() override;
    bool validateOrder() override;
    std::ostream& print(std::ostream &out) const override;
};

class AdvanceOrder : public Order {
public:
    void executeOrder() override;
    bool validateOrder() override;
    std::ostream& print(std::ostream &out) const override;
};

class BombOrder : public Order {
public:
    void executeOrder() override;
    bool validateOrder() override;
    std::ostream& print(std::ostream &out) const override;
};

class BlockadeOrder : public Order {
public:
    void executeOrder() override;
    bool validateOrder() override;
    std::ostream& print(std::ostream &out) const override;
};

class AirliftOrder : public Order {
public:
    void executeOrder() override;
    bool validateOrder() override;
    std::ostream& print(std::ostream &out) const override;
};

class NegotiateOrder : public Order {
public:
    void executeOrder() override;
    bool validateOrder() override;
    std::ostream& print(std::ostream &out) const override;
};

class OrdersList {
public:
    void addOrder(std::unique_ptr<Order> order);
    std::unique_ptr<Order>& getOrder(size_t index);
    void moveOrder(size_t from, size_t to);
    void removeOrder(size_t index);
    friend std::ostream& operator<<(std::ostream &out, const OrdersList &list);

private:
    std::vector<std::unique_ptr<Order>> orders;
};

#endif // ORDERS_H
