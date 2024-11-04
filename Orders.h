#ifndef ORDERS_H
#define ORDERS_H

#include "Player.h"
#include "OrdersDriver.h"

#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <random>

class Player;
class Territory;

// Base class representing a general order in the game
class Order {
public:
    Order(); //default constructor
    Order(const Order& original); //copy constructor
    virtual ~Order(); //destructor to ensure proper cleanup in derived classes

    //A pure virtual method --> function in a base class that has no implementation and 
    //must be overriden by derived classes, making the base class abstract

    //Virtual methods that must be implemented by derived classes
    virtual bool validateOrder() = 0;    // Validate if the order can be executed
    virtual void executeOrder() = 0;     // Execute the order if it is valid -> apply the order effect to the game state

    //Overloaded stream insertion operator for printing order details
    friend std::ostream& operator<<(std::ostream& outputStream, const Order& order); //overloaded stream insertion operator
    
    //Overloaded assignment operator for proper copying of order objects
    //Overloaded stream insertion operator -> define how an object's details are printed using std::cout
    Order& operator = (const Order& orginal); //assignment operator

    virtual void execute() = 0;

protected:
    std::string orderDescription; //description of the order -> eg. deploy armies
    std::string orderEffect; //effect of the order once executed -> eg. armies have been deployed
    bool executed; //track if the order has been executed to prevent re-execution
};

// Derived classes for each type of order 

// Derived class for the 'deploy' order in the game
class Deploy : public Order {

private:

    Player* player;
    int armies;
    Territory* target;

public:
    Deploy(); //constructor
    Deploy(Player*, int, Territory*);
    ~Deploy(); //destrcutor

    bool validateOrder() override; //validate if the deploy order can be executed
    void executeOrder() override; //execute the deploy order --> deploy armies in the game

    void execute() override;

};

// Derived class for the 'advance' order in the gamne
class Advance : public Order {

private:

    Player* player;
    int armies;
    Territory* source;
    Territory* target;

public:
    Advance(); //constructor
    Advance(Player*,int,Territory*,Territory*);
    ~Advance(); //destructor

    bool validateOrder() override; //validate if the advance order can be executed
    void executeOrder() override; //execute the advance order --> move armies between territories

    void execute() override;

    int getRand();
};

// Derived class for the 'bomb' order in the game
class Bomb : public Order {

private:

    Player* player;
    Territory* target;

public:
    Bomb(); //constructor
    Bomb(Player*,Territory*);
    ~Bomb(); //destructor

    bool validateOrder() override; //validate if the bomb order can be executed
    void executeOrder() override; //execute the bomb order --> destroy half of the army units

    void execute() override;
};

// Derived class for the 'blokade' order in the game
class Blockade : public Order {

private:

    Player* player;
    Territory* target;

public:
    Blockade(); //constructor
    Blockade(Player*,Territory*);
    ~Blockade(); //destructor

    bool validateOrder() override; //validate if the blockade order can be executed
    void executeOrder() override; //execute the blockade order --> triple army units and make territories neutral

    void execute() override;
};

// Derived class for the 'airlift' order in the game
class Airlift : public Order {

private:

    Player* player;
    int armies;
    Territory* source;
    Territory* target;

public:
    Airlift(); //constructor
    Airlift(Player*,int,Territory*,Territory*);
    ~Airlift(); //destructor

    bool validateOrder() override; //validate if the airlift order can be executed
    void executeOrder() override; //execute the airlift order --> move some units 

    void execute() override;

};

// Derived class for the 'negotiate' order in the game
class Negotiate : public Order {

private:

    Player* player;
    Player* targetPlayer;

public:
    Negotiate(); //constructor
    Negotiate(Player*,Player*);
    ~Negotiate(); //destructor

    bool validateOrder() override; //validate if the negotiate order can be executed
    void executeOrder() override; //execute the negotiate order --> prevent attacks between 2 players

    void execute() override;
};

// Class to manage a list of orders --> operations like adding, moving, and removing orders
class OrdersList {
public:
    OrdersList(); //constructor
    ~OrdersList(); //destructor
    
    void addOrder(Order* order); //add a new order to the list
    void move(int fromIndex, int toIndex); //move an order from one position to another within a list
    void remove(int index); //remove an order from the lsit --> using index

    //Overload stream insertion operator for printing the lsit of orders
    friend std::ostream& operator<<(std::ostream& outputStream, const OrdersList& ordersList);

    std::vector<Order*> getOrders(); //get the list of orders
private:
    //Vector to store pointers to orders
    //Polymorphism - storing different order types
    std::vector<Order*> orders;
};

static vector<pair<Player*,Player*>> negotiatePairs;

bool checkNegotiatePairs(Player*,Player*);
void addNegotiatePairs(Player*,Player*);
void resetNegotiatePairs();

#endif // ORDERS_H
