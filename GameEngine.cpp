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
GameEngine::GameEngine() : currentState(GameStateStrings[0]) {
    
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
    //    Notify(this);
}

std::string GameEngine::stringToLog() {
    return "GameEngine changed state to " + std::string(currentState);
}

//function to process console commands
void GameEngine::processConsoleCommand(std::string& command, CommandProcessor* commandProcessor) {

    Command* cmd = commandProcessor->getCommand(command);
    std::cout << "\nCurrent State: " << getCurrentState() << "\n" << std::endl;
    if((commandProcessor->validate(cmd, this->getCurrentState())) == true) {
        stateTransition(cmd); //command is good
    } else {
        std::cout << "Invalid command. Try again.\n" << std::endl;
    }
};

//function to process file commands 
void GameEngine::processFileCommand(std::string& command, CommandProcessor* commandProcessor) {

    Command* cmd = nullptr;
    while ((cmd = commandProcessor->getCommand(command)) != nullptr) {
        std::cout << "\nCurrent State: " << getCurrentState() << "\n" << std::endl;
        if((commandProcessor->validate(cmd, this->getCurrentState())) == true) {
            stateTransition(cmd);
        } else {
            std::cout << "Invalid command. Try again.\n" << std::endl;
        }
    }   
    std::cout << "\nNo more commands to process.\nCurrent State: " << getCurrentState() << "\n" << std::endl;
    delete cmd;
    exit(0);
}

void GameEngine::startupPhase() {
    std::string inputMode;
    bool useConsole = false;
    std::cout << "Welcome to the Game Engine!\n\n" << "Choose a mode to input commands: \n" << "1. Console\n" << "2. File\n" << "\nEnter 1 or 2:\n" << "> ";
    std::cin >> inputMode;

     // Select the appropriate CommandProcessor based on command-line argument
    CommandProcessor* commandProcessor = nullptr;
    FileLineReader* fileLineReader = nullptr;

    if (inputMode == "1") {
        commandProcessor = new CommandProcessor();
        useConsole = true;
    } 
    else if (inputMode == "2") {
        std::string fileName;
        while (true) {
            std::cout << "\nEnter the file name: ";
            std::cin >> fileName;
            try {
                fileLineReader = new FileLineReader(fileName);
                commandProcessor = new FileCommandProcessorAdapter(fileLineReader);
                break;
            } catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } 

    else {
        std::cerr << "\nInvalid input mode. Exiting..." << std::endl;
        return;
    }

    GameEngine engine;
    std::cout << "\nStarting Game Engine\n\n";

    std::string input;
    std::string unknown = "";

    while (true) {
        if(useConsole) {
            std::cout << "Type a command " << std::endl;
            std::cout << "> ";
            std::getline(std::cin >> std::ws, input);
            engine.processConsoleCommand(input, commandProcessor);
            
            // switch (input) {
            //     case "loadmap":

            //         break;
            //     case "validatemap":
            //         break;
            //     case "addplayer": 
            //         break;  
            //     case "gamestart":
            //         break;
                
            // }

            if (input == "exit") {
                break;
            }
        }
        else {
            engine.processFileCommand(unknown, commandProcessor);
        }
        
        
        // Command* cmd = commandProcessor->getCommand(input);
        // if (!cmd) {
        //     break;
        // }
        
        // if (cmd->getCommandStr() == "exit") {
        //     delete cmd;
        //     cmd = nullptr;
        //     break;
        // }
    }

    
    delete commandProcessor;
    delete fileLineReader;
    commandProcessor = nullptr;
    fileLineReader = nullptr;



}



