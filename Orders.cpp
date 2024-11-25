#include "Orders.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Base class order implementation
Order::Order()
{
    Attach(NULL);
    orderDescription = "undefined";
    orderEffect = "none";
    executed = false;
}

// constructor --> initializes an Order with default values
Order::Order(Observer *o) : orderDescription("undefined"), orderEffect("none"), executed(false)
{
    Attach(o);
}

// Destructor --> ensure derived class destructors are called properly
Order::~Order() {}

// Assignment operator --> handles deep copying of the order data

// Deep copying is necessary to ensure that each copy of an order has its own distinct memory allocation,
// preventing issues like shared state or accidental modifications to the original order when working with multiple instances

Order &Order::operator=(const Order &original)
{
    if (this != &original)
    {                                                       // check for self-assignment
        this->orderDescription = original.orderDescription; // copy order description
        this->orderEffect = original.orderEffect;           // copy order effect
        this->executed = original.executed;                 // copy execution status
    }
    return *this;
}

// Overloaded stream isnertion operator for printing order details
std::ostream &operator<<(std::ostream &outputStream, const Order &order)
{
    outputStream << "The order: " << order.orderDescription;

    // if the order has been executed, print its effect
    if (order.executed)
    {
        outputStream << " ~~~ The effect: " << order.orderEffect;
    }
    return outputStream; // return the output stream
}

std::string Order::stringToLog()
{
    return orderDescription + " had effect " + orderEffect;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Deploy Order - derived class Deploy implementation

// Constructor sets the order description specific to deploy
Deploy::Deploy()
{
    orderDescription = "Deploy order - place armies on a territory";
}

Deploy::Deploy(Observer *o, Player *p, int a, Territory *t) : Order(o), player(p), armies(a), target(t)
{
    orderDescription = "Deploy order ";
} // parameterized constructor

Deploy::~Deploy()
{ // Deploy Destructor

    delete player;
    player = NULL;
    delete target;
    target = NULL;

} // destructor

// Validate if the deploy order can be executed
bool Deploy::validateOrder()
{
    for (Territory *t : player->getTerritories())
        if (target == t)
            return player->getReinforcementPool() >= armies; // target Territory needs to belong to the player issuing the order

    return false;
}

// Execute the deploy order and set its effect
void Deploy::executeOrder()
{
    target->setNumArmies(target->getNumArmies() + armies); // sending a number of troops to another Territory
    player->setReinforcementPool(player->getReinforcementPool() - armies);

    executed = true;                                                                                                          // mark the order as executed
    orderEffect = to_string(armies) + " units have been deployed to " + target->getName() + " by " + player->getPlayerName(); // set the order effect
    Notify(this);
}

void Deploy::execute()
{
    if (!this->validateOrder())
    {
        cout << target->getName() << " is not deployed " << armies << " amount of armies when they have " << player->getReinforcementPool() << " and " << player->getReinforcementTemp() << endl;
        cout << "\nDeploy Order is not valid for player " << player->getPlayerName() << endl; // invalid Order message

        return;
    }

    cout << "\nDeploy Order is valid - > " << player->getPlayerName() << " is deploying " << armies << " units to Territory " << target->getName() << endl;
    cout << target->getName() << " now has " << target->getNumArmies() << " armies" << endl;

    this->executeOrder(); // executing the Order after checking to see if it is valid
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Advance Order - derived class

// Constructor sets the porder description to advance
Advance::Advance()
{
    orderDescription = "Advance Order";
}

Advance::Advance(Observer *o, Player *p, int a, Territory *s, Territory *t) : Order(o), player(p), armies(a), source(s), target(t)
{
    orderDescription = "Advance Order ";
} // parameterized constructor

Advance::~Advance()
{ // Advance destructor

    delete player;
    player = NULL;
    delete source;
    source = NULL;
    delete target;
    target = NULL;

} // destructor

// Validate if the advance order can be executed
bool Advance::validateOrder()
{
    bool validOwnership = false; // verify if the source Territory is owned by the player issuing the Order
    bool validAdj = false;       // target Territory needs to be adjacent to source Territory

    for (Territory *t : player->getTerritories())
    {
        if (source == t)
        {
            validOwnership = true; // source Territory is owned by player issuing the order
            return validOwnership;
            // break;
        }
    }

    for (Territory *t : source->getAdjTerritories())
    {
        if (target == t)
        {
            validAdj = true; // target Territory is adjacent to source Territory

            // validates that if the two players (or one) owning both Territories are in a truce for the round
            // and checks if the amount of troops being sent is lower than the amount of troops present in the source Territory
            return validAdj && !checkNegotiatePairs(player, target->getPlayer()) && source->getNumArmies() >= armies;
            // break;
        }
    }

    cout << player->getPlayerName() << " tried to advance to " << target->getName() << " which is not a territory they own nor an adjacent territory !" << endl;
    return false;

    // updated to remove the loop and just get the player from the target player
    // return validAdj && !checkNegotiatePairs(player, target->getPlayer()) && source->getNumArmies() >= armies;
    // } // the above validates that if the two players (or one) owning both Territories are in a truce for the round
    // and checks if the amount of troops being sent is lower than the amount of troops present in the source Territory
}

// Execute the advance order and set its effect
void Advance::executeOrder()
{

    bool attack = true;

    for (Territory *t : player->getTerritories())
    {
        if (target == t)
        {
            attack = false; // determines if the Advance order is an attack, or a deployment of troops to a friendly Territory
            break;
        }
    }

    if (attack)
    { // Attack simulation

        cout << "Battle begins!" << endl;

        source->setNumArmies(source->getNumArmies() - armies);

        int attackerNum = armies;
        int defenderNum = target->getNumArmies();

        while (attackerNum != 0 && defenderNum != 0)
        {

            if (getRandomNum() <= 60)
                defenderNum--; // random chance of an attacking army unit killing a defender
            if (getRandomNum() <= 70)
                attackerNum--; // random chance of a defending army unit killing an attacker
        }

        if (defenderNum == 0)
        { // if the defending army has no troops remaining on its Territory -> defenders lose

            cout << "The defending army has lost the battle! Transferring ownership of Territory " << target->getName() << " to " << player->getPlayerName() << endl;

            bool found = false;

            for (Player *p : getPlayerList())
            {

                for (Territory *t : p->getTerritories())
                {

                    if (t == target)
                    {

                        p->removeTerritory(t); // removes Territory from the defending player's Territory list
                        found = true;
                        break;
                    }
                }

                if (found)
                    break;
            }


            if (player->getCanDrawCard())
            { // checks to see if the player can draw a Card this round

                Deck *deck = new Deck();

                Card *c = deck->draw(); // player draws a Card from the Deck

                cout << player->getPlayerName() << " has drawn a " << c->getCardType() << " card for conquering a Territory!" << endl;

                // added the card into its list
                player->addCard(c);

                player->drewCard(); // player cannot draw another card this round

                delete deck;
                deck = NULL;
                cout << "test 2" << endl;
            }
            target->setPlayer(player);         // adds ownership of new player to target territory
            player->addTerritory(target);      // adds Territory to the attacking player
            target->setNumArmies(attackerNum); // sets number of army units on the target Territory to the remaining number of attackers
        }
        else
        { // defending army has won

            cout << "The defending army has won the battle!" << endl;
            // added
            target->setNumArmies(defenderNum);
        }
    }
    else
    { // no battle has occurred, transferring units to target territory

        cout << "No battle, both Territories belong to " << player->getPlayerName() << endl;
        source->setNumArmies(source->getNumArmies() - armies);
        target->setNumArmies(target->getNumArmies() + armies);
    }

    executed = true;
    orderEffect = to_string(armies) + " units have been advanced from " + source->getName() + " to " + target->getName() + " by " + player->getPlayerName();
    Notify(this);
}

void Advance::execute()
{
    if (!this->validateOrder())
    {
        cout << "\nAdvance Order is not valid for player " << player->getPlayerName() << endl; // invalid Order message
        return;
    }
    cout << "\nAdvance Order is valid -> " << player->getPlayerName() << " is advancing " << armies << " units from Territory " << source->getName() << " to Territory " << target->getName() << endl;

    this->executeOrder(); // executes Order
}

int Advance::getRandomNum()
{ // returns a random number in the range of 1-100

    random_device random;
    mt19937 gen(random());
    std::uniform_int_distribution<int> range(1, 100);
    return range(random);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Bomb Order - derived class

// Constructor sets the order description specific to bomb order
Bomb::Bomb()
{
    orderDescription = "Bomb Order - bomb a territory to weaken its defense";
}

Bomb::Bomb(Observer *o, Player *p, Territory *t) : Order(o), player(p), target(t) // parameterized constructor for the Bomb class
{
    orderDescription = "Bomb Order ";
}

Bomb::~Bomb()
{ // Bomb destructor

    delete player;
    player = NULL;
    delete target;
    target = NULL;

} // destructor

// Validate if the bomb order can be executed
bool Bomb::validateOrder()
{

    for (Territory *t : player->getTerritories())
    {
        if (target == t)
        {
            cout << player->getPlayerName() << " can't bomb its own territory " << target->getName() << " !" << endl;
            return false; // checks to see if the target Territory is owned by the player issuing the Order
        }
    }

    bool validAdj = false;

    for (Territory *t : target->getAdjTerritories())
    {

        for (Territory *t2 : player->getTerritories())
        { //
          // validates that the target Territory is adjacent to at least
            if (t == t2)
            {                    // one Territory owned by the player issuing the Order
                validAdj = true; //
                break;
            }
            if (validAdj)
                break;
        }
    }

    // for (Player *p : getPlayerList())
    // {

    //     for (Territory *t : p->getTerritories())
    //     {

    //         if (t == target)
    return validAdj && !checkNegotiatePairs(player, target->getPlayer());

    // } // the above validates if the player issuing the order and the player owning the target territory are in a truce this round
    //     }

    //     return false;
}

// Execute the bomb order and set its effect
void Bomb::executeOrder()
{

    target->setNumArmies(target->getNumArmies() / 2); // killing half the army units on the target territory

    executed = true;
    orderEffect = "Territory " + target->getName() + " has been bombed by " + player->getPlayerName();
    Notify(this);
}

void Bomb::execute()
{

    if (!this->validateOrder())
    {
        cout << "\nBomb Order is not valid for player " << player->getPlayerName() << endl; // invalid order message
        return;
    }

    cout << "\nBomb Order is valid -> " << player->getPlayerName() << " is bombing Territory " << target->getName() << endl;

    this->executeOrder();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Blockade Order - derived class

// Constructor sets the order description specific to blockade order
Blockade::Blockade()
{
    orderDescription = "Blockade Order - blockade a territory to prevent movement";
}

Blockade::Blockade(Observer *o, Player *p, Territory *t) : Order(o), player(p), target(t) // paramterized constructor for the Blockade class
{
    orderDescription = "Blockade Order ";
}

Blockade::~Blockade()
{ // Blockade destructor

    delete player;
    player = NULL;
    delete target;
    target = NULL;

} // destructor

// Validate if the blockade order can be executed
bool Blockade::validateOrder()
{
    // Placeholder logic for validation

    for (Territory *t : player->getTerritories())
    {

        if (t == target)
            return true; // validates to see if the target Territory is owned by the player issuing the Order
    }
    cout << player->getPlayerName() << " doesn't own territory " << target->getName() << endl;
    return false;
}

// Execute the bloackade order and set its effect
void Blockade::executeOrder()
{
    player->removeTerritory(target); // removes target Territory from the territory list of the player issuing the Order

    // bool neutralCreated = false;

    // for (Player *p : getPlayerList())
    // {

    //     if ((p->getPlayerName().compare("Neutral")) == 0)
    //     { // if the neutral player already exists

    //         p->addTerritory(target); // adds Territory to the neutral player's list
    //         neutralCreated = true;
    //         break;
    //     }
    //     if (neutralCreated)
    //         break;
    // }

    // if (!neutralCreated)
    // { // if the neutral player doesnt already exist

    //     Player *n = new Player(observer, "Neutral"); // creates Neutral player

    //     addToPlayerList(n); // adds the neutral player to the list

    //     n->addTerritory(target); // adds the territory to the neutral player's list
    // }

    target->setNumArmies(target->getNumArmies() * 2); // doubles the number of units on the target Territory

    executed = true;
    orderEffect = "Territory " + target->getName() + "has been blockaded by " + player->getPlayerName();
    Notify(this);
}

void Blockade::execute()
{

    if (!this->validateOrder())
    {
        cout << "\nBlockade Order is not valid for player " << player->getPlayerName() << endl; // invalid order message
        return;
    }

    cout << "\nBlockade Order is valid - > " << player->getPlayerName() << " is transferring the ownership of Territory " << target->getName() << " to the Neutral player, army units doubled to: " << target->getNumArmies() << endl;
    this->executeOrder();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Airlift Order - derived class

// Constructor sets the order description specific to airlift
Airlift::Airlift()
{
    orderDescription = "Airlift Order - move armies from one territory to another by air";
}

Airlift::Airlift(Observer *o, Player *p, int a, Territory *s, Territory *t) : Order(o), player(p), armies(a), source(s), target(t) // parameterized constructor for the Airlift class
{
    orderDescription = "Airlift Order ";
}

Airlift::~Airlift()
{ // destructor for the Airlift class

    delete player;
    player = NULL;
    delete source;
    source = NULL;
    delete target;
    target = NULL;

} // destructor

// Validate if the airlift order can be executed
bool Airlift::validateOrder()
{
    // Placeholder logic for validation

    bool validSource = false;
    bool validTarget = false;

    for (Territory *t : player->getTerritories())
    { // validates that both the target and source territory are owned by the player issuing the Order

        if (t == source)
            validSource = true;
        if (t == target)
            validTarget = true;
    }

    return validSource && validTarget && armies <= source->getNumArmies(); // also validates that the amount of troops being moved is lesser or equal than the amount present on the source territory
}

// Execute the airlift order and set its effect
void Airlift::executeOrder()
{

    source->setNumArmies(source->getNumArmies() - armies); // transferring a given amount of troops from source to target
    target->setNumArmies(target->getNumArmies() + armies); //

    executed = true;
    orderEffect = "Armies have been airlifted from " + source->getName() + " to " + target->getName() + " by " + player->getPlayerName();
    Notify(this);
}

void Airlift::execute()
{

    if (!this->validateOrder())
    {
        cout << "\nAirlift Order is not valid for player " << player->getPlayerName() << endl; // invalid order message
        return;
    }

    cout << "\nAirlift Order is valid -> " << player->getPlayerName() << " is transferring " << armies << " from Territory " << source->getName() << " to Territory " << target->getName() << endl;

    this->executeOrder();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Negotiate Order - derived class

// Constructor sets the order description specific to negotiate
Negotiate::Negotiate()
{
    orderDescription = "Negotiate Order - negotiate a truce with another player";
}

Negotiate::Negotiate(Observer *o, Player *p1, Player *p2) : Order(o), player(p1), targetPlayer(p2) // parameterized constructor for Negotiate class
{
    orderDescription = "Negotiate Order ";
}

Negotiate::~Negotiate()
{ // destructor for negotiate class

    delete player;
    player = NULL;
    delete targetPlayer;
    targetPlayer = NULL;

} // destructor

// Validate if the negoatiate order can be executed
bool Negotiate::validateOrder()
{

    return player != targetPlayer && !checkNegotiatePairs(player, targetPlayer); // validates that the target player is not the same as the player issuing the order
} // also validates to see if the pair is not already in a truce

// Execute the negotiate order and set its effect
void Negotiate::executeOrder()
{

    addNegotiatePairs(player, targetPlayer); // adds this pair of players to the list

    executed = true;
    orderEffect = "Truce has been negotiated between " + player->getPlayerName() + " and " + targetPlayer->getPlayerName();
    Notify(this);
}

void Negotiate::execute()
{

    if (!this->validateOrder())
    {
        cout << "\nNegotiate Order is not valid for player " << player->getPlayerName() << endl; // invalid Order message
        return;
    }

    cout << "\nNegotiate Order is valid -> " << player->getPlayerName() << " and " << targetPlayer->getPlayerName() << " cannot attack eachother this round" << endl;

    this->executeOrder();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// OrdersList class implementation

// Constructor for OrdersList
OrdersList::OrdersList(Observer *o)
{
    Attach(o);
}

// Destructor for OrdersList --> ensure all dynamically allocated orders are deleted
OrdersList::~OrdersList()
{
    for (Order *order : orders)
    {
        delete order;
        order = NULL;
    }
}

// Add an order to the list
void OrdersList::addOrder(Order *order)
{
    orders.push_back(order);
    Notify(order);
}

// Move an order from one position to another in the list
void OrdersList::move(int fromIndex, int toIndex)
{
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size())
    {
        std::swap(orders[fromIndex], orders[toIndex]);
    }
}

// Remove an order from the list by its index
void OrdersList::remove(int index)
{
    if (index >= 0 && index < orders.size())
    {
        delete orders[index];
        orders.erase(orders.begin() + index);
    }
}

// Overload stream insertion operator for printing the list of orders
std::ostream &operator<<(std::ostream &out, const OrdersList &ordersList)
{
    for (size_t i = 0; i < ordersList.orders.size(); ++i)
    {

        // Print each order using the overloaded << operator
        out << *ordersList.orders[i] << std::endl;
    }
    return out;
}

vector<Order *> OrdersList::getOrders()
{
    return orders;
}

void OrdersList::clearOrders()
{
    orders.clear();
}

bool checkNegotiatePairs(Player *p1, Player *p2)
{ // returns a boolean to check if 2 players are in a truce this round

    for (pair<Player *, Player *> p : negotiatePairs)
    { // using ADT pair

        if ((p.first == p1 && p.second == p2) || p.first == p2 && p.second == p1)
            return true;
    }
    return false;
}

void addNegotiatePairs(Player *p1, Player *p2)
{ // adds 2 players to the negotiatepairs pair

    pair<Player *, Player *> pear = make_pair(p1, p2);

    negotiatePairs.push_back(pear);
}

void resetNegotiatePairs()
{ // after each round, we clear the truces

    negotiatePairs.clear(); // clears the vector
}

void addToPlayerList(Player *p)
{ // test method

    playerList.push_back(p);
}

vector<Player *> getPlayerList()
{ // tets method
    return playerList;
}

void clearPlayerList()
{
    playerList.clear();
}

void removePlayerFromList(Player* p){

    playerList.erase(std::remove(playerList.begin(), playerList.end(), p), playerList.end());

}

std::string OrdersList::stringToLog()
{
    std::string logString = "Current Orders List: \n";
    for (Order *order : orders)
    {
        logString += "\t" + order->stringToLog() + "\n";
    }
    return logString;
}