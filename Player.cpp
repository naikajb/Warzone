/**
 * PLAYER CLASS FEATURES:
 * 1. Player owns collection of Territory objects
 * 2. Player owns a hand of Card objects
 * 3. Player contains methods toDefend(), toAttack()
 * 4. Player contains issueOrder() method to creates and Order object and adds it to the list
 * 5. Driver names testPlayers() method to test the Player class
 */

#include "Player.h"
using namespace std;

Player::Player() {
    orders = new OrdersList(); 
}

Player :: Player(const Player& orig){

    //copy every territory from the original player to the new player
    for (Territory* territories: orig.territories){
        this->territories.push_back(territories);
    }

    //copy every card from the original player to the new player
    for (Card* card: orig.hand){
        this->hand.push_back(card);
    }

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