#include "GameEngine.h"

//defining the GameState constructor
GameState::GameState(){};

//defining the copy constructor
GameState::GameState(const GameState& gameState) {
    std::cout << "Copy Constructor of GameState";
};

//defining the destructor
GameState::~GameState(){};

StartState::StartState(){};

StartState::StartState(const StartState& startState){
    std::cout << "Copy Constructor of StartState";
};

StartState::~StartState(){};

//handleCommand function implementation, it processes the command and each state decides what to do with the received command
void StartState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "loadmap"){
        std::cout << "Loading map..." << std::endl;
        engine->changeState(engine->getMapLoadedState()); //transition to next state

    } else {
        std::cout << "Invalid command. Try <loadmap> to move to next step.\n" << std::endl;
    }
};

//StartState's getstatename: returns the name of the state
std::string StartState::getStateName(){
    return "Start";
};

MapLoadedState::MapLoadedState(){};

MapLoadedState::MapLoadedState(const MapLoadedState& mapLoadedState) {
    std::cout << "Copy Constructor of MapLoadedState";
};

MapLoadedState::~MapLoadedState(){};

void MapLoadedState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "loadmap") {
        std::cout << "Loading map...\n" << std::endl;
    }
    else if (command == "validatemap") {
        std::cout << "Validating map...." << std::endl;
        engine->changeState(engine->getMapValidated());
    }
    else {
        std::cout << "Invalid command. try <validatemap> to move to next step or <loadmap> to load another map.\n" << std::endl;
    }
};

std::string MapLoadedState::getStateName(){
    return "Map Loaded";
}

MapValidatedState::MapValidatedState(){};

MapValidatedState::MapValidatedState(const MapValidatedState& mapValidatedState) {
    std::cout << "Copy Constructor of MapValidatedState";
}

MapValidatedState::~MapValidatedState(){};

void MapValidatedState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "addplayer") {
        std::cout << "adding player...." << std::endl;
        engine->changeState(engine->getPlayersAdded());
    }
    else {
        std::cout << "Invalid command. try <addplayer> to move to next step.\n" << std::endl;
    }
};

std::string MapValidatedState::getStateName() {
    return "Map Validated";
}

PlayersAddedState::PlayersAddedState(){};
PlayersAddedState::PlayersAddedState(const PlayersAddedState& PlayersAddedState) {
    std::cout << "Copy Constructor of PlayersAddedState";
}

PlayersAddedState::~PlayersAddedState(){};

void PlayersAddedState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "addplayer") {
        std::cout << "adding player....\n" << std::endl;
    }
    else if (command == "assigncountries") {
        std::cout << "Assigning countries...." << std::endl;
        engine->changeState(engine->getAssignReinforcement());
    }

    else {
        std::cout << "Invalid command. try <assigncountries> to move to next step or <addplayer> if you want to add more players.\n" << std::endl;
    }

};

std::string PlayersAddedState::getStateName() {
    return "Players Added";
}

AssignReinforcementState::AssignReinforcementState(){};

AssignReinforcementState::AssignReinforcementState(const AssignReinforcementState& assignReinf) {
    std::cout << "Copy Constructor of AssignReinforcementState";
}

AssignReinforcementState::~AssignReinforcementState(){};

void AssignReinforcementState::handleCommand(GameEngine* engine, const std::string& command) {
     if (command == "issueorder") {
        std::cout << "Issuing order...." << std::endl;
        engine->changeState(engine->getIssueOrders());
    }
    else {
        std::cout << "Invalid command. try <issueorder> to move to next step.\n" << std::endl;
    }
}

std::string AssignReinforcementState::getStateName() {
    return "Assign Reinforcement";
}

IssueOrdersState::IssueOrdersState(){};

IssueOrdersState::IssueOrdersState(const IssueOrdersState& issueOrderState) {
    std::cout << "Copy Constructor of IssueOrderState";
};

IssueOrdersState::~IssueOrdersState(){};

void IssueOrdersState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "issueorder") {
        std::cout << "Issuing order....\n" << std::endl;
    }
    else if (command == "endissueorders") {
        std::cout << "Ending issue orders...." << std::endl;
        engine->changeState(engine->getExecuteOrders());
    }
    else {
        std::cout << "Invalid command. try <endissueorders> to move to next step or <issueorder>.\n" << std::endl;
    }
}

std::string IssueOrdersState::getStateName() {
    return "Issue Orders";
}

ExecuteOrdersState::ExecuteOrdersState(){};

ExecuteOrdersState::ExecuteOrdersState(const ExecuteOrdersState& executeOrderState) {
    std::cout << "Copy Constructor of ExecuteOrderState";
}

ExecuteOrdersState::~ExecuteOrdersState(){};

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
        std::cout << "Invalid command. try <endexecorders> or <win> to move to next step or <execorder>.\n" << std::endl;
    }
}

std::string ExecuteOrdersState::getStateName() {
    return "Execute Orders";
}

WinState::WinState(){};

WinState::WinState(const WinState& winState) {
    std::cout << "Copy Constructor of WinState";
};

WinState::~WinState(){};

void WinState::handleCommand(GameEngine* engine, const std::string& command) {
    if (command == "play") {
        std::cout << "Continuing Game...." << std::endl;
        engine->changeState(engine->getStartState());
    }
    else if (command == "end") {
        exit(-1);
    }
    else {
        std::cout << "Invalid command. try <play> to continue playing or <end>.\n" << std::endl;
    }
}

std::string WinState::getStateName() {
    return "Win!";
}

// initializing the CurrentState pointer 
GameEngine::GameEngine(): currentState(nullptr){
    startState = new StartState(); // creating instances of the State classes
    mapLoadedState = new MapLoadedState();
    mapValidated = new MapValidatedState();
    playersAdded = new PlayersAddedState();
    assignReinforcement = new AssignReinforcementState();
    issueOrders = new IssueOrdersState();
    executeOrders = new ExecuteOrdersState();
    win = new WinState();
    currentState = startState; // set the pointer to the first State.
}

GameEngine::GameEngine(const GameEngine& game_engine){
    std::cout << "Copy constructor of Game Engine\n";
};

// deallocating all the objects created
GameEngine::~GameEngine(){
    delete startState;
    delete mapLoadedState;
    delete mapValidated;
    delete playersAdded;
    delete assignReinforcement;
    delete issueOrders;
    delete executeOrders;
    delete win;
    startState = NULL;
    mapLoadedState = NULL;
    mapValidated = NULL;
    playersAdded = NULL;
    assignReinforcement = NULL;
    issueOrders = NULL;
    executeOrders = NULL;
    win = NULL;
};

// Getters for the different states (definitions)
GameState* GameEngine::getStartState() {
    return startState;
}

GameState* GameEngine::getMapLoadedState() {
    return mapLoadedState;
}

GameState* GameEngine::getMapValidated() {
    return mapValidated;
}

GameState* GameEngine::getPlayersAdded() {
    return playersAdded;
}

GameState* GameEngine::getAssignReinforcement() {
    return assignReinforcement;
}

GameState* GameEngine::getIssueOrders() {
    return issueOrders;
}

GameState* GameEngine::getExecuteOrders() {
    return executeOrders;
}

GameState* GameEngine::getWin() {
    return win;
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

// Constructor definition, using the initializer list to initialize the 'engine' member
CommandParser::CommandParser(GameEngine* engine) : engine(engine){};

CommandParser::CommandParser(const CommandParser& commandParser){};

CommandParser::~CommandParser(){};

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




