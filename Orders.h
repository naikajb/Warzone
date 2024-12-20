#ifndef ORDERS_H
#define ORDERS_H

#include "Player.h"
#include "OrdersDriver.h"
#include "LoggingObserver.h"
#include "PlayerStrategies.h"

#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <random>
#include <utility>
#include <type_traits>
#include <algorithm>

using std::pair;
using std::vector;

class Player;
class Territory;

// Base class representing a general order in the game
class Order : public ILoggable, public Subject
{
public:
    Order();                      // default constructor
    Order(Observer *);            // constructor
    Order(const Order &original); // copy constructor
    virtual ~Order();             // destructor to ensure proper cleanup in derived classes

    // A pure virtual method --> function in a base class that has no implementation and
    // must be overriden by derived classes, making the base class abstract

    // Virtual methods that must be implemented by derived classes
    virtual bool validateOrder() = 0; // Validate if the order can be executed
    virtual void executeOrder() = 0;  // Execute the order if it is valid -> apply the order effect to the game state

    // Overloaded stream insertion operator for printing order details
    friend std::ostream &operator<<(std::ostream &outputStream, const Order &order); // overloaded stream insertion operator

    // Overloaded assignment operator for proper copying of order objects
    // Overloaded stream insertion operator -> define how an object's details are printed using std::cout
    Order &operator=(const Order &orginal); // assignment operator
    std::string stringToLog() override;     // convert the order to a string for logging
    virtual void execute() = 0;

protected:
    std::string orderDescription; // description of the order -> eg. deploy armies
    std::string orderEffect;      // effect of the order once executed -> eg. armies have been deployed
    bool executed;                // track if the order has been executed to prevent re-execution
};

// Derived classes for each type of order

// Derived class for the 'deploy' order in the game
class Deploy : public Order
{

private:
    Player *player;
    int armies;
    Territory *target;

public:
    Deploy(); // constructor
    Deploy(Observer *, Player *, int, Territory *);
    ~Deploy(); // destrcutor

    bool validateOrder() override; // validate if the deploy order can be executed
    void executeOrder() override;  // execute the deploy order --> deploy armies in the game

    void execute() override;
};

// Derived class for the 'advance' order in the gamne
class Advance : public Order
{

private:
    Player *player;
    int armies;
    Territory *source;
    Territory *target;

public:
    Advance(); // constructor
    Advance(Observer *, Player *, int, Territory *, Territory *);
    ~Advance(); // destructor

    bool validateOrder() override; // validate if the advance order can be executed
    void executeOrder() override;  // execute the advance order --> move armies between territories

    void execute() override;

    int getRandomNum();
};

// Derived class for the 'bomb' order in the game
class Bomb : public Order
{

private:
    Player *player;
    Territory *target;

public:
    Bomb(); // constructor
    Bomb(Observer *, Player *, Territory *);
    ~Bomb(); // destructor

    bool validateOrder() override; // validate if the bomb order can be executed
    void executeOrder() override;  // execute the bomb order --> destroy half of the army units

    void execute() override;
};

// Derived class for the 'blokade' order in the game
class Blockade : public Order
{

private:
    Player *player;
    Territory *target;

public:
    Blockade(); // constructor
    Blockade(Observer *, Player *, Territory *);
    ~Blockade(); // destructor

    bool validateOrder() override; // validate if the blockade order can be executed
    void executeOrder() override;  // execute the blockade order --> triple army units and make territories neutral

    void execute() override;
};

// Derived class for the 'airlift' order in the game
class Airlift : public Order
{

private:
    Player *player;
    int armies;
    Territory *source;
    Territory *target;

public:
    Airlift(); // constructor
    Airlift(Observer *, Player *, int, Territory *, Territory *);
    ~Airlift(); // destructor

    bool validateOrder() override; // validate if the airlift order can be executed
    void executeOrder() override;  // execute the airlift order --> move some units

    void execute() override;
};

// Derived class for the 'negotiate' order in the game
class Negotiate : public Order
{

private:
    Player *player;
    Player *targetPlayer;

public:
    Negotiate(); // constructor
    Negotiate(Observer *, Player *, Player *);
    ~Negotiate(); // destructor

    bool validateOrder() override; // validate if the negotiate order can be executed
    void executeOrder() override;  // execute the negotiate order --> prevent attacks between 2 players

    void execute() override;
};

// Class to manage a list of orders --> operations like adding, moving, and removing orders
class OrdersList : public ILoggable, public Subject
{
public:
    OrdersList(Observer *); // constructor
    ~OrdersList();          // destructor

    void addOrder(Order *order);           // add a new order to the list
    void move(int fromIndex, int toIndex); // move an order from one position to another within a list
    void remove(int index);                // remove an order from the lsit --> using index
    void clearOrders();

    // Overload stream insertion operator for printing the lsit of orders
    friend std::ostream &operator<<(std::ostream &outputStream, const OrdersList &ordersList);

    std::vector<Order *> getOrders();   // get the list of orders
    std::string stringToLog() override; // convert the list of orders to a string for logging

private:
    // Vector to store pointers to orders
    // Polymorphism - storing different order types
    std::vector<Order *> orders;
};

static vector<pair<Player *, Player *>> negotiatePairs;

bool checkNegotiatePairs(Player *, Player *);
void addNegotiatePairs(Player *, Player *);
void resetNegotiatePairs();

static vector<Player *> playerList;

vector<Player *> getPlayerList();
void addToPlayerList(Player *);
void removePlayerFromList(Player*);

void clearPlayerList();

#endif // ORDERS_H
