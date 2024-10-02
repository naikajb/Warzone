//definitions + local declarations
#include "GameEngine.h"


//handleCommand function implementation, command processing happens and each state decides what to do with the received command
void StartState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "loadmap"){
        std::cout << "Loading map..." << std::endl;
        engine->changeState(engine->getMapLoadedState()); //transition to next state

    } else {
        std::cout << "Invalid command. Try <loadmap> to move to next step." << std::endl;
    }
};

//StartState's getstatename: returns the name of the state
std::string StartState::getStateName(){
    return "Start";
};

void MapLoadedState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "loadmap") {
        std::cout << "Loading map...\n" << std::endl;
    }
    else if (command == "validatemap") {
        std::cout << "Validating map...." << std::endl;
        engine->changeState(engine->getMapValidated());
    }
    else {
        std::cout << "Invalid command. try <validatemap> to move to next step or <loadmap> to load another map." << std::endl;
    }
};

std::string MapLoadedState::getStateName(){
    return "Map Loaded";
}

void MapValidatedState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "addplayer") {
        std::cout << "adding player...." << std::endl;
        engine->changeState(engine->getPlayersAdded());
    }
    else {
        std::cout << "Invalid command. try <addplayer> to move to next step." << std::endl;
    }
};

std::string MapValidatedState::getStateName() {
    return "Map Validated";
}

void PlayersAddedState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "addplayer") {
        std::cout << "adding player....\n" << std::endl;
    }
    else if (command == "assigncountries") {
        std::cout << "Assigning countries...." << std::endl;
        engine->changeState(engine->getAssignReinforcement());
    }

    else {
        std::cout << "Invalid command. try <assigncountries> to move to next step or <addplayer> if you want to add more players." << std::endl;
    }

};

std::string PlayersAddedState::getStateName() {
    return "Players Added";
}

void AssignReinforcementState::handleCommand(GameEngine* engine, const std::string& command) {
     if (command == "issueorder") {
        std::cout << "Issuing order...." << std::endl;
        engine->changeState(engine->getIssueOrders());
    }
    else {
        std::cout << "Invalid command. try <issueorder> to move to next step." << std::endl;
    }
}

std::string AssignReinforcementState::getStateName() {
    return "Assign Reinforcement";
}

void IssueOrdersState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "issueorder") {
        std::cout << "Issuing order....\n" << std::endl;
    }
    else if (command == "endissueorders") {
        std::cout << "Ending issue orders...." << std::endl;
        engine->changeState(engine->getExecuteOrders());
    }
    else {
        std::cout << "Invalid command. try <endissueorders> to move to next step or <issueorder>." << std::endl;
    }
}

std::string IssueOrdersState::getStateName() {
    return "Issue Orders";
}

void ExecuteOrdersState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "execorder") {
        std::cout << "Executing Order....\n" << std::endl;
    }
    else if (command == "win") {
        std::cout << "Win...." << std::endl;
        engine->changeState(engine->getWin());
    }
    else if (command == "endexecorders") {
        std::cout << "Ending Execute Order...." << std::endl;
        engine->changeState(engine->getAssignReinforcement());
    }
    else {
        std::cout << "Invalid command. try <endexecorders> or <win> to move to next step or <execorder>." << std::endl;
    }
}

std::string ExecuteOrdersState::getStateName() {
    return "Execute Orders";
}

void WinState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "play") {
        std::cout << "Continuing Game...." << std::endl;
        engine->changeState(engine->getStartState());
    }
    else if (command == "end") {
        exit(-1);
    }
    else {
        std::cout << "Invalid command. try <play> to continue playing or <end>." << std::endl;
    }
}

std::string WinState::getStateName() {
    return "Win!";
}

// Delegate command to the current state's handleCommand method
void GameEngine::handleCommand(const std::string& command) {
    currentState->handleCommand(this, command);
}

// GameEngine's change state method, the current state pointer is updated to point to the newState passed as parameter
void GameEngine::changeState(GameState* newState) {
    currentState = newState;
    std::cout << "State changed to: " << currentState->getStateName() << "\n" << std::endl;
}

// CommandParser's parseCommand function definition which checks if a command is valid before delegating it to the handleCommand function 
void CommandParser::parseCommand(const std::string& input) {
    std::istringstream iss(input); // creating object of istringstream
    std::string commandType;
    iss >> commandType; // stream the input to string commandType

    // using find function to search for the value input inside the vector
    if (std::find(commands.begin(), commands.end(), commandType) != commands.end()) { // if std::find does not find element, it returns commands.end()
        engine->handleCommand(commandType);

    } else {
        std::cout << "Unknown command: " << commandType << ". Try Again\n"<< std::endl;
    }
}




