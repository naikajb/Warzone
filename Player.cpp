/**
 * PLAYER CLASS FEATURES:
 * 1. Player owns collection of Territory objects
 * 2. Player owns a hand of Card objects
 * 3. Player contains methods toDefend(), toAttack() returning abitrary lists of territories to defend/attack
 * 4. Player contains issueOrder() method to creates and Order object and adds it to the list
 * 5. Driver names testPlayers() method to test the Player class
 */

#include "Player.h"
using namespace std;

Player::Player(string playerName) {
    this->playerName = playerName;
    orders = new OrdersList(); 
}

Player :: Player(const Player& orig){

    //copy every territory from the original player to the new player
    for (Territory* territories: orig.territories){
        this->territories.push_back(territories);
    }

    //copy every card from the original player to the new player
    hand = new Hand(*orig.hand);

    //copy every order from the original player to the new player
    orders = new OrdersList(*orig.orders);
}

// Player destructor
Player::~Player() {
    // for (Order* order: orders->getOrders()){
    //     delete order;
    // }
    delete orders; //TODO: check if i need to delete the orders in the list first

    for (Territory* territory: territories){
        delete territory;
    }
    //TODO: check if i need to delete the cards in the hand first
}

// adds order to the player's list of orders
void Player::issueOrder(Order* order){
    orders->addOrder(order);
}

// adds territory to the player's list of territories
void Player::addTerritory(Territory* territory){
    territories.push_back(territory);
} 

// returns ARBITRARY list of territories to defend
vector<Territory*> Player::toDefend(){
    vector<Territory*> toDefend;
    if (territories.size() == 0){
        cout << "Player has no territories to defend" << endl;
        return toDefend;
    }
    for (int i = 0; i < territories.size(); i++){
        if (i % 2 == 0){
            toDefend.push_back(territories[i]);
        }
    } 
    return toDefend;
}

// returns ARBITRARY list of territories to attack
vector<Territory*> Player::toAttack(){
    vector<Territory*> toAttack;
    
    if (territories.size() == 0){
        cout << "Player has no territories to attack" << endl;
        return toAttack;
    }

    for (int i = 0; i < territories.size(); i++){
        if (i % 2 != 0){
            toAttack.push_back(territories[i]);
        }
    } 
    return toAttack;
}

std::string Player::getPlayerName(){
    return playerName;
}

//adds card to player's Hand
void Player::addCard(Card* card){
    hand->addCard(card);
}

//removes territory from player's list of territories
void Player::removeTerritory(Territory* territory){
    for (int i = 0; i < territories.size(); i++){
        if (territories[i] == territory){
            territories.erase(territories.begin() + i);
            break;
        }
    }
}

void Player::printPlayer(){
    cout << "Player name: " << playerName 
            << "\n  Number of Territories: " << territories.size() 
            << "\n  Current OrderList: " << orders->getOrders().size() 
            << endl;
    
}