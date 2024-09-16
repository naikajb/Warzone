#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <vector>
#include <string>

class Order{
public:
    Order(); //constructor
    virtual ~Order(); //destructor

    virtual bool validateOrder() const = 0; //pure virtual method for validation
    virtual void executeOrder() = 0; //pure virtual method for execution

    friend std::ostream& operator<<(std::ostream& out, const Order& order);

protected:
    std::string OrderDescription; //description of the order
    std::string OrderEffect; //effect of the order after execution
    bool isExecuted; //checking if the order has been execur
};

class DeployOrder : public Order {
public:
    DeployOrder();
    ~DeployOrder();
    bool validateOrder() const override;
    void executeOrder() override;
};

class AdvanceOrder : public Order {
public:
    AdvanceOrder();
    ~AdvanceOrder();
    bool validateOrder() const override;
    void executeOrder() override;
};

class BombOrder : public Order {
public:
    BombOrder();
    ~BombOrder();
    bool validateOrder() const override;
    void executeOrder() override;
};

class BlockadeOrder : public Order {
public:
    BlockadeOrder();
    ~BlockadeOrder();
    bool validateOrder() const override;
    void executeOrder() override;
};

class AirliftOrder : public Order {
public:
    AirliftOrder();
    ~AirliftOrder();
    bool validateOrder() const override;
    void executeOrder() override;
};

class NegotiateOrder : public Order {
public:
    NegotiateOrder();
    ~NegotiateOrder();
    bool validateOrder() const override;
    void executeOrder() override;
};

class OrdersList {
public:
    OrdersList();
    ~OrdersList();

    void addOrder(std::unique_ptr<Order> order); //add an order to the list
    void moveOrder(int fromIndex, int toIndex); //move an order in the list
    void removeOrder(int index); //delete an order from the list

    //stream insertion operator to output the list of orders
    friend std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList);

private:
    std::vector<std::unique_ptr<Order>> orders; //list of orders

};

#endif //#ifndef ORDERS_H