#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"
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

    // function to handle the startup phase
    void startupPhase();
    
    // copy constructor
    GameEngine(const GameEngine& game_engine);

    // destructor
    virtual ~GameEngine();

     // process file commands
    void processFileCommand(std::string& command, CommandProcessor* commandProcessor);

    // process console commands
    void processConsoleCommand(std::string& command, CommandProcessor* commandProcessor);

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