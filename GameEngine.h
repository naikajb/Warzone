#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <map>
#include <random>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
using namespace std;


class GameEngine : public Subject, public ILoggable  {
public:
    // declaring constructor
    GameEngine();

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

    std::string stringToLog();

    // function that handles changing states
    void stateTransition(Command* cmd);

    // function to get the current state
    const char* getCurrentState();

    // map to store the state transitions
    multimap<std::string, const char*> stateTransitionMap;
    static const char* GameStateStrings[];

    // function to get the random numbers
    vector<int> getRandomizedNumbers(int n);

private:
    const char* currentState;
    CommandProcessor* commandProcessor;
};

#endif