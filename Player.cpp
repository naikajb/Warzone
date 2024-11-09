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

Player::Player(string playerName)
{
    this->playerName = playerName;
    orders = new OrdersList();
    reinforcementPool = 50; // added
}

Player ::Player(const Player &orig)
{

    // copy every territory from the original player to the new player
    for (Territory *territories : orig.territories)
    {
        this->territories.push_back(territories);
    }

    // copy every card from the original player to the new player
    hand = new Hand(*orig.hand);

    // copy every order from the original player to the new player
    orders = new OrdersList(*orig.orders);

    // added
    reinforcementPool = orig.reinforcementPool;
}

// Player destructor
Player::~Player()
{
    // for (Order* order: orders->getOrders()){
    //     delete order;
    // }
    delete orders; // TODO: check if i need to delete the orders in the list first

    for (Territory *territory : territories)
    {
        delete territory;
    }
    // TODO: check if i need to delete the cards in the hand first
}

std::vector<Territory *> Player::getTerritories()
{
    return territories;
}

void Player::setReinforcementPool(int armies)
{
    reinforcementPool = armies;
}
int Player::getReinforcementPool()
{
    return reinforcementPool;
}

// adds order to the player's list of orders
void Player::issueOrder(Order *order)
{
    orders->addOrder(order);
    // cout << *order << endl;
}

// adds territory to the player's list of territories
void Player::addTerritory(Territory *territory)
{
    territories.push_back(territory);
}

// returns list of territories to defend based on priority
// for now the priority is:
// 1. has adjacent territories that are not player's and has enemy armies (its based on who has more)
// 2. has adjacent territories that are not the player's and has no enemy armies
// 3. has adjacent territories that are the player's
vector<Territory *> Player::toDefend()
{
    cout << "Before the sort: \n" <<  endl;

    sort(territories.begin(), territories.end(), [this](Territory *t1, Territory *t2)
         {
        // number of enemy armies for territory 1
        int numArmiesT1 = 0;
        // number of enemy armies for territory 2
        int numArmiesT2 = 0;

        // if both territories have 0 enemy armies
        // priority changes to number of enemy territories OR
        // unowned territories surrounding Territory 1
        int numEnemyAdjT1 = 0;
        // number of enemy territories OR unowned territories
        // surrounding Territory 2
        int numEnemyAdjT2 = 0;

        for (Territory* t : t1->getAdjTerritories()){
            if (t->getPlayerOwner() != this){
                numArmiesT1 += t->getNumArmies();
                numEnemyAdjT1++;
            }
        }

        for (Territory* t : t2->getAdjTerritories()){
            if (t->getPlayerOwner() != this){
                numArmiesT2 += t->getNumArmies();
                numEnemyAdjT2++;
            }
        }    

        cout << "\n" << t1->getName() << " with " << numArmiesT1 << " enemy armies and " << numEnemyAdjT1 << " adjacent enemy territories !" << endl;
        cout << t2->getName() << " with " << numArmiesT2 << " enemy armies and " << numEnemyAdjT2 << " adjacent enemy territories !\n" << endl;

        if (numArmiesT1 == 0 && numArmiesT2 == 0)
            {   
                // Sort in descending order based on the number of adajcent enemy territories OR 
                // adjacent unnowned territories 
                return numEnemyAdjT1 > numEnemyAdjT2;
            }
        // Sort in descending order based on the number of enemy armies
        return numArmiesT1 > numArmiesT2; 
        });
    cout << "\nAfter the sort: \n" << endl;
        for (Territory *t : territories){
        cout << t->getName() << ": " << t->getNumArmies() << endl;
    }
    return territories;
}

// returns ARBITRARY list of territories to attack
vector<Territory *> Player::toAttack()
{
    vector<Territory *> toAttack;

    if (territories.size() == 0)
    {
        cout << "Player has no territories to attack" << endl;
        return toAttack;
    }

    for (int i = 0; i < territories.size(); i++)
    {
        if (i % 2 != 0)
        {
            toAttack.push_back(territories[i]);
        }
    }
    return toAttack;
}

// stream insertion operator to print player's information
ostream &operator<<(ostream &out, const Player &player)
{
    out << "Player name: " << player.playerName << endl;
    out << "Territories owned: " << player.territories.size() << endl;
    for (Territory *territory : player.territories)
    {
        out << "\t" << territory->getName() << endl;
    }
    return out;
}

std::string Player::getPlayerName()
{
    return playerName;
}

// adds card to player's Hand
void Player::addCard(Card *card)
{
    hand->addCard(card);
}

// removes territory from player's list of territories
void Player::removeTerritory(Territory *territory)
{
    for (int i = 0; i < territories.size(); i++)
    {
        if (territories[i] == territory)
        {
            territories.erase(territories.begin() + i);
            break;
        }
    }
}

// attach observer to player's order list
void Player::AttachObserver(Observer *observer)
{
    orders->Attach(observer);
}
