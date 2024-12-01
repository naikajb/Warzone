#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <map>
#include <cmath>
#include <random>
#include <typeinfo>
#include "LoggingObserver.h"

#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;
using std::vector; // added 
using std::floor;

void testStartupPhase();
void testMainGameLoop();
class GameEngine : public Subject, public ILoggable  {
public:
    // declaring constructor
    GameEngine(Observer*);

    // function to handle the startup phase
    void startupPhase();
    
    // copy constructor
    GameEngine(const GameEngine& game_engine);

    // destructor
    virtual ~GameEngine();

     // process file commands
    bool processFileCommand(std::string& command, CommandProcessor* commandProcessor);

    // process console commands
    bool processConsoleCommand(std::string& command, CommandProcessor* commandProcessor);

    std::string stringToLog() override;

    // function that handles changing states
    void stateTransition(Command* cmd);

    // function to get the current state
    const char* getCurrentState();

    // map to store the state transitions
    multimap<std::string, const char*> stateTransitionMap;
    static const char* GameStateStrings[];

    // added Main Game Loop part of the game
    void reinforcementPhase(vector <Player*>, Map *map, int round);
    void issueOrdersPhase(vector <Player*>, int round);
    void executeOrdersPhase(vector <Player*>);
    void mainGameLoop(vector <Player*>, Map *map);

    // function to get the random numbers
    vector<int> getRandomizedNumbers(int n);

private:
    const char* currentState;
    CommandProcessor* commandProcessor;
    Observer* observer;
};

#endif