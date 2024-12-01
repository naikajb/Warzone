#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include <iostream> // import library that provides objects which can read user input and output data to the console or to a file
#include <string>   // import library to use string features
#include <vector>   // import library to use vectors
#include <list>     // import library to use list features
#include <sstream>  // import library to use string streams
#include <fstream>  // import library to input and output stream class to operate on files
#include "Player.h"
#include "Orders.h"
#include "Map.h"

#include <typeinfo>

class Order;
class Territory;
class Player;

using namespace std;
class PlayerStrategy
{
private:
    Player *player;
    string ps;

public:
    virtual ~PlayerStrategy();
    virtual void issueOrder(Order *) = 0;
    virtual vector<Territory *> toAttack() = 0;
    virtual vector<Territory *> toDefend() = 0;
    void assignPlayer(Player *);
    void becomeAggressive();
    Player *getPlayer();
    void setPlayer(Player *);
    bool contains(vector<Territory *>, Territory *);
    virtual string getPlayerType();
};

void checkNeutralAttack(Territory *);

class Human : public PlayerStrategy
{
public:
    void issueOrder(Order *);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string getPlayerType();
};

class Aggressive : public PlayerStrategy
{
public:
    void issueOrder(Order *);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string getPlayerType();
    // Territory *randomTerritoryToAttack();
    Territory *randomTerritoryToDefend();
};

class Benevolent : public PlayerStrategy
{
public:
    void issueOrder(Order *);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string getPlayerType();
    Territory *randomTerritoryToDefend();
};

class Neutral : public PlayerStrategy
{
public:
    void issueOrder(Order *);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string getPlayerType();
};

class Cheater : public PlayerStrategy
{
private:
    bool canConquer = true;

public:
    void issueOrder(Order *);
    vector<Territory *> toAttack();
    vector<Territory *> toDefend();
    string getPlayerType();
    bool cheaterCanConquer();
    void resetCheaterConquer();
    void isConquering();
};

bool compareArmiesBenevolent(Territory *, Territory *);
bool compareArmiesAggressive(Territory *, Territory *);

#endif
