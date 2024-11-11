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

Player::Player(Observer *o, string playerName)
{
    this->playerName = playerName;
    orders = new OrdersList(o);
    canDrawCard = true;
    reinforcementPool = 50;

    // temp value of the reinforcement pool for the issuing order phase
    hand = new Hand();
    territories = vector<Territory *>();
    // this is so that the values of the reinforcement pool can be manipulated/modfied without the actual execution of it (issue order phase)
    reinforcementTemp = 50;
    observer = o;
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

Hand *Player::getHand()
{
    return hand;
}

OrdersList *Player::getOrderList()
{
    return orders;
}

// adds order to the player's list of orders
void Player::issueOrder(Order *order)
{

    // the randomizer picks a random territory to defend and to attack everytime
    // the issueOrder is called

    // random device rd
    std::random_device rd;
    // generator seeded by rd for random numbers
    std::mt19937 gen(rd());

    // randomizer using a probability for toDefend

    // a vector of the same size as toDefend vector, where the first element has the highest weight
    // and the last element the lowest weight
    // the higher the value, the higher the probability
    // this is so that the toDefend vector has a higher probability to have the higher priority
    // territories to be chosen
    vector<double> probabilityToDefend;
    for (int i = 0; i < toDefend().size(); i++)
    {
        probabilityToDefend.push_back(toDefend().size() - i);
    }

    // use a discrete distribution called distToDefend using the weight values of the probabilityToDefend
    // this means that when drawing a random number, indexes with higher weight will have a bigger probability
    // to be chosen (the weight with higher values is placed in the same index as the toDefend vector)
    std::discrete_distribution<> distToDefend(probabilityToDefend.begin(), probabilityToDefend.end());
    int randomIndexDefend = distToDefend(gen); // get a random index

    Territory *selectedTerritoryToDefend = toDefend()[randomIndexDefend]; // choose a territory to defend with random index

    // randomizer using a probability for toAttack

    // a vector of the same size as toAttack vector, where the first element has the highest weight
    // and the last element the lowest weight
    // the higher the value, the higher the probability
    // this is so that the toAttack vector has a higher probability to have the higher priority
    // territories to be chosen
    vector<double> probabilityToAttack;
    for (int i = 0; i < toAttack().size(); i++)
    {
        probabilityToAttack.push_back(toAttack().size() - i);
    }

    // use a discrete distribution called distToAttack using the weight values of the probabilityToAttack
    // this means that when drawing a random number, indexes with higher weight will have a bigger probability
    // to be chosen (the weight with higher values is placed in the same index as the toAttack vector)
    std::discrete_distribution<> distToAttack(probabilityToAttack.begin(), probabilityToAttack.end());
    int randomIndexAttack = distToAttack(gen); // get a random index

    Territory *selectedTerritoryToAttack = toAttack()[randomIndexAttack]; // choose a territory to attack with random index

    // if the order is of type deploy
    if (Deploy *d = dynamic_cast<Deploy *>(order))
    {
        // choose a random number of army units to deploy
        // reinforcement temp is used to keep track of the reinforcement pool
        // without actually modifying it until the order execution
        int min = 0;
        int max = reinforcementTemp;
        std::uniform_int_distribution<> distRandArmiesDeploy(min, max);
        int randomNumArmiesDeploy = distRandArmiesDeploy(gen);

        // deploy random number of army units to a random territory to defend
        Deploy *dep = new Deploy(observer, this, randomNumArmiesDeploy, selectedTerritoryToDefend);

        reinforcementTemp -= randomNumArmiesDeploy;

        // add order to order list
        orders->addOrder(dep);
        return;
    }

    // if the order is of type advance
    if (Advance *a = dynamic_cast<Advance *>(order))
    {
        // decide randomly if player wants to attack or defend
        int defend = 0;
        int attack = 1;
        std::uniform_int_distribution<> distAttackOrDefend(defend, attack);
        int answer = distAttackOrDefend(gen);
        // cout << "the answer is: " << answer << " for player "<< this->getPlayerName() << endl;

        // attack
        if (answer == 1)
        {
            // cout << randomIndexAttack << " is the index of vector and attack territory is: " << selectedTerritoryToAttack->getName() << endl;
            // go through all the territories the player has
            for (Territory *t : territories)
            {
                // check if the territory is adjacent to the one selected to attack
                for (Territory *tadj : t->getAdjTerritories())
                {
                    // if the territory is adjacent to the one selected to attack
                    // AND it has more than 1 army unit
                    if (selectedTerritoryToAttack->getName().compare(tadj->getName()) == 0 && t->getNumArmiesTemp() >= 1)
                    {
                        // choose a random number of armies to send from the player's territory to the selected territory to attack
                        // numArmiesTemp is to be able to modify and keep track of the number of armies in a territory
                        // without actually modifying the number of armies the territory has until order execution
                        int min = 0;
                        int max = t->getNumArmiesTemp();
                        std::uniform_int_distribution<> distAttackAdvance(min, max);
                        int numArmiesAttack = distAttackAdvance(gen);

                        // advance
                        Advance *adv = new Advance(observer, this, numArmiesAttack, t, selectedTerritoryToDefend);
                        // add order to orderlist
                        orders->addOrder(adv);
                        // cout << "the territory to attack is : " << selectedTerritoryToAttack->getName() << "\nand the territory chosen from the player to attack with is: " << t->getName() << "\nthe number of armies to attack with is: " << numArmiesAttack << "\nthe number of armies it originally had was: " << t->getNumArmiesTemp() << endl;
                        // keep track of the number of armies the territory can actually advance with
                        t->setNumArmiesTemp(t->getNumArmiesTemp() - numArmiesAttack);

                        return;
                    }
                }
            }
        }

        // defend
        else
        {
            // cout << randomIndexDefend << " is the index of vector and defend territory is: " << selectedTerritoryToDefend->getName() << endl;
            // go through all the territories the player has
            for (Territory *t : territories)
            {
                // check if the territory is adjacent to the one selected to defend
                for (Territory *tadj : t->getAdjTerritories())
                {
                    // if the territory is adjacent to the one selected to defend
                    // AND it has more than 1 army unit
                    // AND it is not the same territory
                    if (selectedTerritoryToDefend->getName().compare(tadj->getName()) && t->getNumArmiesTemp() >= 1 && t->getName().compare(selectedTerritoryToDefend->getName()) != 0)
                    {
                        // choose a random number of armies to send from the player's territory to the selected territory to derend
                        // numArmiesTemp is to be able to modify and keep track of the number of armies in a territory
                        // without actually modifying the number of armies the territory has until order execution
                        int min = 0;
                        int max = t->getNumArmiesTemp();
                        std::uniform_int_distribution<> distDefendAdvance(min, max);
                        int numArmiesDefend = distDefendAdvance(gen);

                        // advance
                        Advance *adv = new Advance(observer, this, numArmiesDefend, t, selectedTerritoryToDefend);
                        // add order to orderlist
                        orders->addOrder(adv);
                        // cout << "the territory to defend is : " << selectedTerritoryToDefend->getName() << "\nand the territory chosen from the player to defend with is: " << t->getName() << "\nthe number of armies to defend with is: " << numArmiesDefend << "\nthe number of armies it originally had was: " << t->getNumArmiesTemp() << endl;
                        // keep track of the number of armies the territory can actually advance with
                        t->setNumArmiesTemp(t->getNumArmiesTemp() - numArmiesDefend);

                        return;
                    }
                }
            }
        }
    }

    // if the order is of type bomb
    if (Bomb *b = dynamic_cast<Bomb *>(order))
    {
        // bomb random selected territory to attack
        cout << this->getPlayerName() << " bomb ! territory: " << selectedTerritoryToAttack->getName() << endl;
        Bomb *bomb = new Bomb(observer, this, selectedTerritoryToAttack);
        orders->addOrder(bomb);
        return;
    }

    // if the order is of type negotiate
    if (Negotiate *n = dynamic_cast<Negotiate *>(order))
    {
        // from a random selected territory to attack, negotiate with the player that owns it
        cout << this->getPlayerName() << " negotiate ! with " << selectedTerritoryToAttack->getPlayer()->getPlayerName() << endl;
        Negotiate *negotiate = new Negotiate(observer, this, selectedTerritoryToAttack->getPlayer());
        orders->addOrder(negotiate);
        return;
    }

    // if the order is of type blockade
    if (Blockade *b = dynamic_cast<Blockade *>(order))
    {
        // blockade random selected territory to attack
        cout << this->getPlayerName() << " blockade ! territory: " << selectedTerritoryToAttack->getName() << endl;
        Blockade *block = new Blockade(observer, this, selectedTerritoryToAttack);
        orders->addOrder(block);
        return;
    }

    // if the order is of type airlift
    if (Airlift *a = dynamic_cast<Airlift *>(order))
    {
        // decide randomly if the player wants to attack or defend
        int defend = 0;
        int attack = 1;
        std::uniform_int_distribution<> distAttackOrDefend(defend, attack);
        int answer = distAttackOrDefend(gen);

        // if the player chooses to attack
        if (answer == 1)
        {
            cout << answer << " attack" << endl;

            // the maximum represents a randomly selected territory to attack, take the player that owns that territory
            // and take the size of the vector of all of its owned territories
            // (this allows a random selection of a territory in the map)
            int min1 = 0;
            int max1 = selectedTerritoryToAttack->getPlayer()->getTerritories().size() - 1;
            std::uniform_int_distribution<> distRandomTerritory(min1, max1);
            int randomTerritory = distRandomTerritory(gen); // from the vector of all of its owned territories, take a random one

            // territory to airlift to
            // chosen from the randomly selected territory to attack, take the player that owns
            // then, choose a randomly selected territory that they own to airlift
            Territory *airlift = selectedTerritoryToAttack->getPlayer()->getTerritories()[randomTerritory];

            // take a random amount of armies from the randomly selected territory from toDefend and airlift
            int min2 = 0;
            int max2 = selectedTerritoryToDefend->getNumArmiesTemp();
            std::uniform_int_distribution<> distAirliftArmies(min2, max2);
            int numArmiesAirlift = distAirliftArmies(gen);

            // airlift
            Airlift *air = new Airlift(observer, this, numArmiesAirlift, selectedTerritoryToDefend, airlift);
            cout << this->getPlayerName() << " airlifts number of armies: " << numArmiesAirlift << " from: " << selectedTerritoryToDefend->getName() << " to: " << airlift->getName() << endl;
            // add order to orderlist
            orders->addOrder(air);
            return;
        }
        // if the player chooses to defend
        else
        {
            cout << answer << " defend" << endl;

            // a while loop to ensure that the randomly generated territory from toDefend() is not the same as
            // the randomly generated territory to airlift to
            while (true)
            {
                // the maximum represents a randomly selected territory to defend based on the player's territories to defend
                int min1 = 0;
                int max1 = toDefend().size() - 1;
                std::uniform_int_distribution<> distRandomTerritory(min1, max1);
                int randomTerritory = distRandomTerritory(gen); // from the vector of all of its owned territories, take a random one

                // territory to airlift to,
                // take a random territory from the toDefend() vector
                Territory *airlift = toDefend()[randomTerritory];

                // if the randomly generated territory from toDefend() is not the same as the randomly generated territory to airlift to,
                // continue the code
                if (selectedTerritoryToDefend->getName().compare(airlift->getName()) != 0)
                {
                    // take a random amount of armies from the randomly selected territory from toDefend and airlift
                    int min2 = 0;
                    int max2 = selectedTerritoryToDefend->getNumArmiesTemp();
                    std::uniform_int_distribution<> distAirliftArmies(min2, max2);
                    int numArmiesAirlift = distAirliftArmies(gen);

                    // airlift
                    Airlift *air = new Airlift(observer, this, numArmiesAirlift, selectedTerritoryToDefend, airlift);
                    cout << this->getPlayerName() << " airlifts number of armies: " << numArmiesAirlift << " from: " << selectedTerritoryToDefend->getName() << " to: " << airlift->getName() << endl;
                    // add order to orderlist
                    orders->addOrder(air);
                    return;
                }
                // if the randomly generated territory from toDefend() is the same as the randomly generated territory to airlift to,
                //  continue the while loop and restart the randomizer for the airlift
                else
                {
                    cout << selectedTerritoryToDefend->getName() << " is the same " << airlift->getName() << endl;
                    continue;
                }
            }
        }
    }
}

// adds territory to the player's list of territories
void Player::addTerritory(Territory *territory)
{
    territories.push_back(territory);
}

vector<Territory *> Player::getTerritories() { return territories; }

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
            if (t->getPlayer() != this){
                numArmiesT1 += t->getNumArmies(); // add number of enemy armies
                numEnemyAdjT1++; // add adjacent enemy territories
            }
        }

        for (Territory* t : t2->getAdjTerritories()){
            if (t->getPlayer() != this){
                numArmiesT2 += t->getNumArmies(); // add number of enemy armies
                numEnemyAdjT2++; // add adjacent enemy territories
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
                     }
                     else
                     {
                        // else increase priority of t1 by 1
                        priorityT1 += 1;
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
                     }
                     else
                     {
                        // else increase priority of t2 by 1
                        priorityT2 += 1;
                     }
                 }
             }

            // sort in descending
            return priorityT1 > priorityT2; });

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

void Player::drewCard() { canDrawCard = false; }
void Player::roundReset() { canDrawCard = true; }
bool Player::getCanDrawCard() { return canDrawCard; }
