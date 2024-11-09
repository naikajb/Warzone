#ifndef GameEngine_h
#define GameEngine_h

#include "CommandProcessor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <map>
#include <cmath>
#include "LoggingObserver.h"
#include "Player.h" //added
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
using namespace std;
using std::vector; // added 
using std::floor;

class GameEngine : public Subject, public ILoggable  {
public:
    // declaring constructor
    GameEngine();

    // copy constructor
    GameEngine(const GameEngine& game_engine);

    // destructor
    virtual ~GameEngine();

     // process commands entered by the user
    void processCommand(std::string& command);

    std::string stringToLog();

    // function that handles changing states
    void stateTransition(Command* cmd);

    // function to get the current state
    const char* getCurrentState();

    // map to store the state transitions
    multimap<std::string, const char*> stateTransitionMap;
    static const char* GameStateStrings[];

    // added Main Game Loop part of the game
    void reinforcementPhase(vector <Player*>, Map *map);
    void issueOrdersPhase(vector <Player*>);
    void executeOrdersPhase(vector <Player*>);
    void mainGameLoop(vector <Player*>);

private:
    const char* currentState;
    CommandProcessor* commandProcessor;
};

#endif