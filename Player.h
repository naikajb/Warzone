#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> 
#include <string>
#include <vector> 
#include <algorithm>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "LoggingObserver.h"
#include "PlayerStrategies.h"
using std::sort;
class OrdersList;
class Order;

class Player{

    private: 
        std::string playerName; // name of the player
        std::vector<Territory*> territories; // collection of Territory objects
        Hand* hand; // hand of Card objects
        OrdersList* orders; // list of Order objects
        bool canDrawCard;
        int reinforcementPool; // nb of armies recieved added
        int reinforcementTemp;
        Observer* observer;
        //PlayerStrategies* strategy;

    public: 
        Player(Observer*,string playerName); //constructor function
        Player(const Player& orig);
        ~Player(); // TODO: implement destructor function 
    
        // Player owns collection of Territory objects
        void addTerritory(Territory* territory);
        void removeTerritory(Territory* territory);

        std::vector<Territory*> getTerritories(); // getter of a list of territories the player has
        void setReinforcementPool(int);
        int getReinforcementPool();
        int getReinforcementTemp();

        std::vector<Territory*> toDefend();  //returns territories to be defended 
        std::vector<Territory*> toAttack();  //returns territories to be attacked
        
        void issueOrder(Order *order);  //adds order to player's list of orders
        
        //stream insertion operator to print player's information
        friend std::ostream& operator<<(std::ostream& out, const Player& player);
        
        void addCard(Card* card);  //adds card to player's hand
        void removeCard(Card* card);  //removes card from player's hand
        Hand *getHand(); // returns players hand

        OrdersList* getOrderList();
        
        void printTerritories();  //prints player's territories
        // void printOrders();  //prints player's orders

        std::string getPlayerName();  //returns player's name

        void AttachObserver(Observer* observer);  //attaches observer to player

        void drewCard();
        void roundReset();
        bool getCanDrawCard();
        
};

#endif // PLAYER_H