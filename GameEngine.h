#ifndef GameEngine_h
#define GameEngine_h

#include "CommandProcessor.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <map>
#include "LoggingObserver.h"
using namespace std;


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

private:
    const char* currentState;
    CommandProcessor* commandProcessor;
};

#endif