#ifndef PLAYER_H
#define PLAYER_H

#include <iostream> 
#include <string>
#include <vector> 
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

class OrdersList;
class Order;

class Player{

    private: 
        std::string playerName; // name of the player
        std::vector<Territory*> territories; // collection of Territory objects
        Hand* hand; // hand of Card objects
        OrdersList* orders; // list of Order objects

    public: 
        Player(string playerName); //constructor function
        Player(const Player& orig);
        ~Player(); //destructor function 
    
        // Player owns collection of Territory objects
        void addTerritory(Territory* territory);
        void removeTerritory(Territory* territory);

        std::vector<Territory*> toDefend();  //returns territories to be defended 
        std::vector<Territory*> toAttack();  //returns territories to be attacked
        
        void issueOrder(Order* order);  //adds order to player's list of orders
        
        //stream insertion operator to print player's information
        friend std::ostream& operator<<(std::ostream& out, const Player& player);
        
        void addCard(Card* card);  //adds card to player's hand
        void removeCard(Card* card);  //removes card from player's hand
        
        vector<Territory*> getTerritories();
        void printTerritories();  //prints player's territories
        void printOrders();  //prints player's orders

        std::string getPlayerName();  //returns player's name
        
};

#endif // PLAYER_H