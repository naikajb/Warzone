#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include <iostream> // import library that provides objects which can read user input and output data to the console or to a file
#include <string>   // import library to use string features
#include <vector>   // import library to use vectors
#include <list>     // import library to use list features
#include <sstream>  // import library to use string streams
#include <fstream>  // import library to input and output stream class to operate on files
#include "Player.h"

using namespace std;
class PlayerStrategy {
    public:
        virtual void issueOrder() = 0;
        virtual void toAttack() = 0;
        virtual void toDefend() = 0;
    private:
        Player* player;
};

class HumanPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder();
        void toAttack();
        void toDefend();
};

#endif
