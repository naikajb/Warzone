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
    canDrawCard = true;
    reinforcementPool = 50; 
    reinforcementTemp = 50; // temp value of the reinforcement pool for the issuing order phase
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

    reinforcementPool = orig.reinforcementPool;
    reinforcementTemp = orig.reinforcementTemp;
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
    reinforcementTemp = armies;
}
int Player::getReinforcementPool()
{
    return reinforcementPool;
}

int Player::getReinforcementTemp()
{
    return reinforcementTemp;
}

Hand * Player::getHand(){
    return hand;
} 

// adds order to the player's list of orders
void Player::issueOrder()
{
    if (reinforcementTemp != 0) {
        Deploy *d = new Deploy();
        orders->addOrder(d);
        reinforcementTemp -= 10; // arbitrary for now
        // add a randomizer with set probabilities for the territory to defend
    }

    

}

// adds territory to the player's list of territories
void Player::addTerritory(Territory *territory)
{
    territories.push_back(territory);
}

vector<Territory*> Player::getTerritories(){return territories;}

// returns list of territories to defend based on priority
// for now the priority is:
// 1. has adjacent territories that are not player's and has enemy armies (its based on who has more)
// 2. has adjacent territories that are not the player's and has no enemy armies
// 3. has adjacent territories that are the player's
vector<Territory *> Player::toDefend()
{

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

        if (numArmiesT1 == 0 && numArmiesT2 == 0)
            {   
                // Sort in descending order based on the number of adajcent enemy territories OR 
                // adjacent unnowned territories 
                return numEnemyAdjT1 > numEnemyAdjT2;
            }
        // Sort in descending order based on the number of enemy armies
        return numArmiesT1 > numArmiesT2; });
    return territories;
}

// returns list of territories to attack based on priority
// for now the priority is:
// 1. adjacent territories are enemy territories and have less armies than the player's territory
// 2. adjacent territories are enemy territories and have have the same nb of armies than the player's territory
// 3. adjacent territories are enemy territories and have more armies than the player's territory
// 4. adjacent territores belongs to the player
vector<Territory *> Player::toAttack()
{
    vector<Territory *> toAttack;

    for (Territory *t : territories)
    {
        for (Territory *tadj : t->getAdjTerritories())
        {
            // check if tadj is not already in the toAttack vector AND the adjacent territory is not part of player's territories
            if (std::find(toAttack.begin(), toAttack.end(), tadj) == toAttack.end() && std::find(territories.begin(), territories.end(), tadj) == territories.end())
            {
                toAttack.push_back(tadj);
            }
        }
    }

    // sorting toAttack() in descendent priority
    sort(toAttack.begin(), toAttack.end(), [this](Territory *t1, Territory *t2)
         {
             int priorityT1 = 0;
             int priorityT2 = 0;

             for (Territory *t : territories)
             {
                // if t1 from toAttack is adjacent to the territory t
                if (std::find(t->getAdjTerritories().begin(), t->getAdjTerritories().end(), t1) != t->getAdjTerritories().end())
                 {
                    // if t1 from toAttack has less armies than territory t
                    if (t1->getNumArmies() < t->getNumArmies())
                     {
                        // increase priority of t1 by 2
                        priorityT1 += 2;
                        cout << t1->getName() << " " << t1->getNumArmies() << " < " << t->getName() << " " << t->getNumArmies() << endl;
                     }
                     else
                     {
                        // else increase priority of t1 by 1
                        priorityT1 += 1;
                        cout << t1->getName() << " " << t1->getNumArmies() << " >= " << t->getName() << " " << t->getNumArmies() << endl;
                     }
                 }
                // if t2 from toAttack is adjacednt to the territory t
                if (std::find(t->getAdjTerritories().begin(), t->getAdjTerritories().end(), t2) != t->getAdjTerritories().end())
                 {
                    // if t2 from toAttack has less armies than territory t                    
                    if (t2->getNumArmies() < t->getNumArmies())
                     {
                        // increase priority of t2 by 2
                        priorityT2 += 2;
                        cout << t2->getName() << " " << t2->getNumArmies() << " < " << t->getName() << " " << t->getNumArmies() << endl;
                     }
                     else
                     {
                        // else increase priority of t2 by 1
                        priorityT2 += 1;
                        cout << t2->getName() << " " << t2->getNumArmies() << " >= " << t->getName() << " " << t->getNumArmies() << endl;
                     }
                 }
             }

            // sort in descending
            return priorityT1 > priorityT2;
         });
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

void Player::drewCard(){canDrawCard = false;}
void Player::roundReset(){canDrawCard = true;}
bool Player::getCanDrawCard(){return canDrawCard;}

