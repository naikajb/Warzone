#include "GameEngine.h"

// creating a list of game states
const char* GameEngine::GameStateStrings[] = {
    "startState",
    "mapLoadedState",
    "mapValidated",
    "playersAdded",
    "assignReinforcement",
    "issueOrders",
    "executeOrders",
    "win"
};

//defining the GameEngine constructor, creating the state transition map which maps commands to the states they transition to
GameEngine::GameEngine() : currentState(GameStateStrings[0]), commandProcessor(new CommandProcessor()) {
    
    stateTransitionMap.insert(pair<std::string, const char*>("loadmap", GameStateStrings[1]));
    stateTransitionMap.insert(pair<std::string, const char*>("validatemap", GameStateStrings[2]));
    stateTransitionMap.insert(pair<std::string, const char*>("addplayer", GameStateStrings[3]));
    stateTransitionMap.insert(pair<std::string, const char*>("gamestart", GameStateStrings[4]));
    stateTransitionMap.insert(pair<std::string, const char*>("replay", GameStateStrings[0]));
};


//defining the copy constructor
GameEngine::GameEngine(const GameEngine& game_engine) {
    std::cout << "Copy Constructor of GameEngine";
};

//defining the destructor
GameEngine::~GameEngine() {
    delete commandProcessor;
    commandProcessor = NULL;
};

//function to get the current state
const char* GameEngine::getCurrentState(){
    return currentState;
}

//function to handle state transitions, it finds the command in the map and changes the state associated with it
void GameEngine::stateTransition(Command* cmd) {
    std::string command = cmd->getCommandStr();

    if (stateTransitionMap.find(command) != stateTransitionMap.end()) {
        currentState = stateTransitionMap.find(command)->second;
        cmd->saveEffect(currentState);
        std::cout << "Changing state to: " << currentState << "...\n" << std::endl;
    }
       Notify(this);
}

std::string GameEngine::stringToLog() {
    return "GameEngine changed state to " + std::string(currentState);
}

//function to process commands entered by the user
void GameEngine::processCommand(std::string& command) {
   
    Command* cmd = commandProcessor->getCommand(command);

    std::cout << "\nCurrent State: " << getCurrentState() << "\n" << std::endl;

    if((commandProcessor->validate(cmd, this->getCurrentState())) == true) {
        stateTransition(cmd);
        
    } else {
        std::cout << "Invalid command. Try again.\n" << std::endl;

    };
}



