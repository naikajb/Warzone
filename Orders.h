#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>  // Include for std::unique_ptr

class Order {
public:
    // Default constructor
    Order();
    
    // Copy constructor
    Order(const Order& other);
    
    // Copy assignment operator
    Order& operator=(const Order& other);

    // Virtual destructor
    virtual ~Order() = default;

    // Pure virtual function for cloning
    virtual std::unique_ptr<Order> clone() const = 0;

    virtual bool validateOrder() const = 0; // Pure virtual method for validation
    virtual void executeOrder() = 0; // Pure virtual method for execution

    friend std::ostream& operator<<(std::ostream& out, const Order& order);

protected:
    std::string OrderDescription; // Description of the order
    std::string OrderEffect; // Effect of the order after execution
    bool isExecuted; // Checking if the order has been executed

private:
    void copyFrom(const Order& other); // Helper function for deep copy
};

class DeployOrder : public Order {
public:
    DeployOrder();
    ~DeployOrder() override;
    bool validateOrder() const override;
    void executeOrder() override;
    std::unique_ptr<Order> clone() const override;
};

class AdvanceOrder : public Order {
public:
    AdvanceOrder();
    ~AdvanceOrder() override;
    bool validateOrder() const override;
    void executeOrder() override;
    std::unique_ptr<Order> clone() const override;
};

class BombOrder : public Order {
public:
    BombOrder();
    ~BombOrder() override;
    bool validateOrder() const override;
    void executeOrder() override;
    std::unique_ptr<Order> clone() const override;
};

class BlockadeOrder : public Order {
public:
    BlockadeOrder();
    ~BlockadeOrder() override;
    bool validateOrder() const override;
    void executeOrder() override;
    std::unique_ptr<Order> clone() const override;
};

class AirliftOrder : public Order {
public:
    AirliftOrder();
    ~AirliftOrder() override;
    bool validateOrder() const override;
    void executeOrder() override;
    std::unique_ptr<Order> clone() const override;
};

class NegotiateOrder : public Order {
public:
    NegotiateOrder();
    ~NegotiateOrder() override;
    bool validateOrder() const override;
    void executeOrder() override;
    std::unique_ptr<Order> clone() const override;
};

class OrdersList {
public:
    OrdersList();
    ~OrdersList();

    void addOrder(std::unique_ptr<Order> order); // Add an order to the list
    void moveOrder(int fromIndex, int toIndex); // Move an order in the list
    void removeOrder(int index); // Delete an order from the list

    // Accessor to get a copy of an order by index
    std::unique_ptr<Order> getOrder(int index) const;

    // Stream insertion operator to output the list of orders
    friend std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList);

    // Copy constructor
    OrdersList(const OrdersList& other);

    // Copy assignment operator
    OrdersList& operator=(const OrdersList& other);

private:
    std::vector<std::unique_ptr<Order>> orders; // List of orders
};

#endif // ORDERS_H
