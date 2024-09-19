#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <vector>
#include <string>

// Base class Order
class Order {
public:
    Order(); //default constructor
    Order(const Order& origal); //copy constructor
    virtual ~Order(); //destructor
    virtual bool validateOrder() = 0;    // Pure virtual method for validation
    virtual void executeOrder() = 0;     // Pure virtual method for execution
    friend std::ostream& operator<<(std::ostream& outputStream, const Order& order); //overloaded stream insertion operator
    Order& operator = (const Order& orginal); //assignment operator

protected:
    //private constant string members for the description and effect of the order
    std::string orderDescription; 
    std::string orderEffect;
    bool executed; //track if the order is executed
};

// Derived classes for each type of order
class Deploy : public Order {
public:
    Deploy();
    ~Deploy();
    bool validateOrder() override;
    void executeOrder() override;
};

class Advance : public Order {
public:
    Advance();
    ~Advance();
    bool validateOrder() override;
    void executeOrder() override;
};

class Bomb : public Order {
public:
    Bomb();
    ~Bomb();
    bool validateOrder() override;
    void executeOrder() override;
};

class Blockade : public Order {
public:
    Blockade();
    ~Blockade();
    bool validateOrder() override;
    void executeOrder() override;
};

class Airlift : public Order {
public:
    Airlift();
    ~Airlift();
    bool validateOrder() override;
    void executeOrder() override;
};

class Negotiate : public Order {
public:
    Negotiate();
    ~Negotiate();
    bool validateOrder() override;
    void executeOrder() override;
};

// Class to manage a list of orders
class OrdersList {
public:
    OrdersList();
    ~OrdersList();
    
    void addOrder(Order* order);
    void move(int fromIndex, int toIndex);
    void remove(int index);
    friend std::ostream& operator<<(std::ostream& outputStream, const OrdersList& ordersList);

private:
    std::vector<Order*> orders;
};

#endif // ORDERS_H
