#include "Orders.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Base class order implementation
// Default constructor --> initializes an Order with default values
Order::Order() : orderDescription("undefined"), orderEffect("none"), executed(false) {}

//Destructor --> ensure derived class destructors are called properly
Order::~Order() {}

//Assignment operator --> handles deep copying of the order data

//Deep copying is necessary to ensure that each copy of an order has its own distinct memory allocation,
//preventing issues like shared state or accidental modifications to the original order when working with multiple instances

Order& Order::operator = (const Order& original){
    if(this != &original){ //check for self-assignment
        this->orderDescription = original.orderDescription; //copy order description
        this->orderEffect = original.orderEffect; //copy order effect
        this->executed = original.executed; //copy execution status
    }
    return *this;
}

//Overloaded stream isnertion operator for printing order details
std::ostream& operator<<(std::ostream& outputStream, const Order& order) {
    outputStream << "The order: " << order.orderDescription;

    //if the order has been executed, print its effect
    if (order.executed) {
        outputStream << " ~~~ The effect: " << order.orderEffect;
    }
    return outputStream; //return the output stream
}

std::string Order::stringToLog() {
    return orderDescription + " had effect " + orderEffect;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Deploy Order - derived class Deploy implementation

// Constructor sets the order description specific to deploy
Deploy::Deploy() {
    orderDescription = "Deploy order - place armies on a territory";
}

Deploy::Deploy(Player* p, int a, Territory* t): player(p), armies(a), target(t)
{orderDescription = "Deploy order - place armies on a territory";}

Deploy::~Deploy() {

    delete player;
    player = NULL;
    delete target;
    target = NULL;

} //destructor

// Validate if the deploy order can be executed 
bool Deploy::validateOrder() {
    
    for(Territory* t : player->getTerritories()) if(target == t) return true;

    return false;
}

// Execute the deploy order and set its effect
void Deploy::executeOrder() {

    target->setNumArmies(target->getNumArmies()+armies);
    executed = true; //mark the order as executed
    orderEffect = "Armies have been deployed."; 
    // Notify(this);
}

void Deploy::execute(){

    if(!this->validateOrder()){
        
        cout << "Deploy Order is not valid for player " << player->getPlayerName() << endl;

        return; }

    cout << "Deploy Order is valid - > " << player->getPlayerName() << " is deploying " << armies << " units to Territory "<< target->getName() << endl;

    this->executeOrder();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Advance Order - derived class 

// Constructor sets the porder description to advance
Advance::Advance() {
    orderDescription = "Advance Order - move armies to an adjacent territory";
}

Advance::Advance(Player* p, int a, Territory* s, Territory* t): player(p), armies(a), source(s), target(t)
{orderDescription = "Advance Order - move armies to an adjacent territory";}

Advance::~Advance() {

    delete player;
    player = NULL;
    delete source;
    source = NULL;
    delete target;
    target = NULL;

} //destructor

// Validate if the advance order can be executed
bool Advance::validateOrder() {
    
    bool validOwnership = false;
    bool validAdj = false;

    for(Territory* t : player->getTerritories()) {
        if(source == t){
            validOwnership = true;
            break;
        }
    }

    for(Territory* t : source->getAdjTerritories()){
        if(target == t){
            validAdj = true;
            break;
        }
    }

    for(Player* p : getPlayerList()){

        for(Territory* t : p->getTerritories()){

            if(t == target) return validAdj && !checkNegotiatePairs(player,p) && source->getNumArmies()>=armies;
           
        }
    }

    return false;
}

// Execute the advance order and set its effect
void Advance::executeOrder() {
    
    bool attack = true;

    for(Territory* t : player->getTerritories()){

        if(target == t){
            attack = false;
            break;
        }
    }

    if(attack){

        cout << "Battle begins!" << endl;

        source->setNumArmies(source->getNumArmies()-armies);

        int attackerNum = armies;
        int defenderNum = target->getNumArmies();

        while(attackerNum!=0 && defenderNum!=0){

            if(getRandomNum() <= 60) defenderNum--;
            if(getRandomNum() <= 70) attackerNum--;
        }

        if(defenderNum == 0){

            cout << "The defending army has lost the battle! Transferring ownership of Territory "<<target->getName()<< " to " << player->getPlayerName() << endl;

            bool found = false;

            for(Player* p : getPlayerList()){

                for(Territory* t : p->getTerritories()){

                    if(t == target){

                        p->removeTerritory(t);
                        found = true;
                        break;
                    }
                }

                if(found) break;
            }

            player->addTerritory(target);
            target->setNumArmies(attackerNum);
        }


    }else{

        cout << "No battle, both Territories belong to " << player->getPlayerName() << endl;
        source->setNumArmies(source->getNumArmies()-armies);
        target->setNumArmies(target->getNumArmies()+armies);

    }

    executed = true; 
    orderEffect = "Armies have advanced.";
    // Notify(this);

}

void Advance::execute(){

    if(!this->validateOrder()){
        
        cout << "Advance Order is not valid for player " << player->getPlayerName() << endl;
        return;
    }
    cout << "Advance Order is valid -> "<< player->getPlayerName() << " is advancing " << armies << " units from Territory " << source->getName() << " to Territory " << target->getName() << endl;

    this->executeOrder();

}

int Advance::getRandomNum(){

    random_device random;
    mt19937 gen(random());
    std::uniform_int_distribution<int> range(1,100);
    return range(random);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Bomb Order - derived class

// Constructor sets the order description specific to bomb order
Bomb::Bomb() {
    orderDescription = "Bomb Order - bomb a territory to weaken its defense";
}

Bomb::Bomb(Player* p, Territory* t): player(p),target(t)
{orderDescription = "Bomb Order - bomb a territory to weaken its defense";}

Bomb::~Bomb() {

    delete player;
    player = NULL;
    delete target;
    target = NULL;

} //destructor

// Validate if the bomb order can be executed
bool Bomb::validateOrder() {
   
    for(Territory* t : player->getTerritories()){
        if(target == t) return false;
    }

    bool validAdj = false;

    for(Territory* t : target->getAdjTerritories()){

        for(Territory* t2 : player->getTerritories()){

            if(t==t2){
                validAdj = true;
                break;
            }
            if(validAdj) break;
        }
    }

    for(Player* p : getPlayerList()){

        for(Territory* t : p->getTerritories()){

            if(t == target) return validAdj && !checkNegotiatePairs(player,p);
           
        }
    }

    return false;
}

// Execute the bomb order and set its effect
void Bomb::executeOrder() {
    
    target->setNumArmies(target->getNumArmies()/2);
    
    executed = true;
    orderEffect = "Territory has been bombed.";
    // Notify(this);
}

void Bomb::execute(){

    if(!this->validateOrder()){
        cout << "Bomb Order is not valid for player " << player->getPlayerName() << endl;
        return;
    }

    cout << "Bomb Order is valid -> "<< player->getPlayerName() << " is bombing Territory "<< target->getName() << endl;

    this->executeOrder();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Blockade Order - derived class

// Constructor sets the order description specific to blockade order
Blockade::Blockade() {
    orderDescription = "Blockade Order - blockade a territory to prevent movement";
}

Blockade::Blockade(Player* p,Territory* t): player(p),target(t)
{orderDescription = "Blockade Order - blockade a territory to prevent movement";}

Blockade::~Blockade() {

    delete player;
    player = NULL;
    delete target;
    target = NULL;

} //destructor

// Validate if the blockade order can be executed 
bool Blockade::validateOrder() {
    // Placeholder logic for validation

    for(Territory* t : player->getTerritories()){

        if(t == target) return true;

    }

    return false;
}

// Execute the bloackade order and set its effect
void Blockade::executeOrder() {
    
    player->removeTerritory(target);

    bool neutralCreated = false;

    for(Player* p : getPlayerList()){

        if((p->getPlayerName().compare("Neutral")) == 0){

            p->addTerritory(target);
            neutralCreated = true;
            break;

        }
        if(neutralCreated) break;
    }

    if(!neutralCreated){

        Player *n = new Player("Neutral");

        addToPlayerList(n);

        n->addTerritory(target);

    }

    target->setNumArmies(target->getNumArmies()*2);
    
    executed = true;
    orderEffect = "Territory has been blockaded.";
    // Notify(this);
}

void Blockade::execute(){

    if(!this->validateOrder()){
        cout << "Blockade Order is not valid for player " << player->getPlayerName() << endl;
        return;
    }
    
    cout << "Blockade Order is valid - > " << player->getPlayerName() << " is transferring the ownership of Territory "<< target->getName() << " to the Neutral player, army units doubled to: "<< target->getNumArmies() << endl;
    this->executeOrder();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Airlift Order - derived class

// Constructor sets the order description specific to airlift
Airlift::Airlift() {
    orderDescription = "Airlift Order - move armies from one territory to another by air";
}

Airlift::Airlift(Player*p, int a, Territory* s, Territory* t): player(p),armies(a), source(s), target(t)
{orderDescription = "Airlift Order - move armies from one territory to another by air";}

Airlift::~Airlift() {

    delete player;
    player = NULL;
    delete source;
    source = NULL;
    delete target;
    target = NULL;

} //destructor

// Validate if the airlift order can be executed 
bool Airlift::validateOrder() {
    // Placeholder logic for validation

    bool validSource = false;
    bool validTarget = false;

    for(Territory* t : player->getTerritories()){

        if(t == source) validSource = true;
        if(t == target) validTarget = true;
    }

    return validSource && validTarget && armies <= source->getNumArmies();
}

// Execute the airlift order and set its effect
void Airlift::executeOrder() {
    
    source->setNumArmies(source->getNumArmies()-armies);
    target->setNumArmies(target->getNumArmies()+armies);
    
    executed = true;
    orderEffect = "Armies have been airlifted";
    // Notify(this);
}

void Airlift::execute(){

    if(!this->validateOrder()){
        cout << "Airlift Order is not valid for player " << player->getPlayerName() << endl;
        return;
    }

    cout << "Airlift Order is valid -> "<< player->getPlayerName() << " is transferring " << armies << " from Territory " << source->getName() << " to Territory " << target->getName() << endl;

    this->executeOrder();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Negotiate Order - derived class

// Constructor sets the order description specific to negotiate
Negotiate::Negotiate() {
    orderDescription = "Negotiate Order - negotiate a truce with another player";
}

Negotiate::Negotiate(Player* p1, Player* p2): player(p1),targetPlayer(p2)
{orderDescription = "Negotiate Order - negotiate a truce with another player";}

Negotiate::~Negotiate() {

    delete player;
    player = NULL;
    delete targetPlayer;
    targetPlayer = NULL;

} //destructor

// Validate if the negoatiate order can be executed
bool Negotiate::validateOrder() {

    return player != targetPlayer && !checkNegotiatePairs(player,targetPlayer);
}

// Execute the negotiate order and set its effect
void Negotiate::executeOrder() {
    
    addNegotiatePairs(player,targetPlayer);

    executed = true;
    orderEffect = "Truce has been negotiated.";
    // Notify(this);
}

void Negotiate::execute(){

    if(!this->validateOrder()){
        cout << "Negotiate Order is not valid for player " << player->getPlayerName() << endl;
        return;
    }

    cout << "Negotiate Order is valid -> "<<player->getPlayerName() << " and " << targetPlayer->getPlayerName() << " cannot attack eachother this round" << endl;

    this->executeOrder();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// OrdersList class implementation

// Constructor for OrdersList
OrdersList::OrdersList() {}

// Destructor for OrdersList --> ensure all dynamically allocated orders are deleted
OrdersList::~OrdersList() {
    for (Order* order : orders) {
        delete order;
        order = NULL;
    }
}

// Add an order to the list
void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
    // Notify(order);
}

// Move an order from one position to another in the list
void OrdersList::move(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < orders.size() && toIndex >= 0 && toIndex < orders.size()) {
        std::swap(orders[fromIndex], orders[toIndex]);
    }
}

// Remove an order from the list by its index
void OrdersList::remove(int index) {
    if (index >= 0 && index < orders.size()) {
        delete orders[index];
        orders.erase(orders.begin() + index);
    }
}

// Overload stream insertion operator for printing the list of orders
std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList) {
    for (size_t i = 0; i < ordersList.orders.size(); ++i) {

        // Print each order using the overloaded << operator
        out << *ordersList.orders[i] << std::endl;
    }
    return out;
}

vector<Order*> OrdersList::getOrders(){
    return orders;
}


bool checkNegotiatePairs(Player* p1, Player* p2){

    for(pair<Player*,Player*> p : negotiatePairs){

        if((p.first == p1 && p.second == p2) || p.first == p2 && p.second == p1) return true;
    }
    return false;
}

void addNegotiatePairs(Player* p1, Player* p2){

    pair<Player*,Player*> pear = make_pair(p1,p2);

    negotiatePairs.push_back(pear);
}

void resetNegotiatePairs(){

    negotiatePairs.clear();
}

void addToPlayerList(Player* p){

    playerList.push_back(p);

}

vector<Player*> getPlayerList(){
    return playerList;
}
std::string OrdersList::stringToLog() {
    std::string logString = "Current Orders List: \n";
    for (Order* order : orders) {
        logString += "\t" + order->stringToLog() + "\n";
    }
    return logString;
}