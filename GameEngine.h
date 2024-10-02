#ifndef GameEngine_h
#define GameEngine_h

#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
#include <algorithm>
using namespace std;

class GameEngine; // forward declaration

//interface for game states which handles transitions when a command is executed
class GameState {
public:
    //default constructor
    GameState() {};

    //copy constructor
    GameState(const GameState& gameState) {
        std::cout << "Copy Constructor of GameState";
    }

    //destructor
    virtual ~GameState(){}

    //pure virtual functions
    virtual void handleCommand(GameEngine* engine, const std::string& command) = 0;
    virtual std::string getStateName() = 0; 
};

// derived classes which represent the different states of the Game Engine
class StartState : public GameState {
public:
    StartState() {};
    StartState(const StartState& startState) {
        std::cout << "Copy Constructor of StartState";
    }
    virtual ~StartState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class MapLoadedState : public GameState {
public: 
    MapLoadedState(){};
    MapLoadedState(const MapLoadedState& mapLoadedState) {
        std::cout << "Copy Constructor of MapLoadedState";
    }
    virtual ~MapLoadedState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class MapValidatedState : public GameState {
public:
    MapValidatedState(){};
    MapValidatedState(const MapValidatedState& mapValidatedState) {
        std::cout << "Copy Constructor of MapValidatedState";
    }
    virtual ~MapValidatedState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;

    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class PlayersAddedState : public GameState {
public:
    PlayersAddedState(){};
    PlayersAddedState(const PlayersAddedState& PlayersAddedState) {
        std::cout << "Copy Constructor of PlayersAddedState";
    }
    virtual ~PlayersAddedState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class AssignReinforcementState : public GameState {
public:
    AssignReinforcementState(){};
    AssignReinforcementState(const AssignReinforcementState& assignReinf) {
        std::cout << "Copy Constructor of AssignReinforcementState";
    }
    virtual ~AssignReinforcementState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class IssueOrdersState : public GameState {
public:
    IssueOrdersState(){};
    IssueOrdersState(const IssueOrdersState& issueOrderState) {
        std::cout << "Copy Constructor of IssueOrderState";
    }
    virtual ~IssueOrdersState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
}; 

class ExecuteOrdersState : public GameState {
public:
    ExecuteOrdersState(){};
    ExecuteOrdersState(const ExecuteOrdersState& executeOrderState) {
        std::cout << "Copy Constructor of ExecuteOrderState";
    }
    virtual ~ExecuteOrdersState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class WinState : public GameState {
public:
    WinState(){};
    WinState(const WinState& winState) {
        std::cout << "Copy Constructor of WinState";
    }
    virtual ~WinState(){};
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

// GameEngine class which manages the current state and provides a function to switch between states
class GameEngine {
public:
    // constructor, initializes the GameEngine with the CurrentState pointer 
    GameEngine() : currentState(nullptr) {
        startState = new StartState(); //creating instances of the State classes
        mapLoadedState = new MapLoadedState();
        mapValidated = new MapValidatedState();
        playersAdded = new PlayersAddedState();
        assignReinforcement = new AssignReinforcementState();
        issueOrders = new IssueOrdersState();
        executeOrders = new ExecuteOrdersState();
        win = new WinState();
        currentState = startState; //make the pointer point to the first State.
    };

    // copy constructor
    GameEngine(const GameEngine& game_engine){
        std::cout << "Copy constructor of Game Engine\n";
    };

    // destructor that deallocates all the objects created
    virtual ~GameEngine(){
        delete startState;
        delete mapLoadedState;
        delete mapValidated;
        delete playersAdded;
        delete assignReinforcement;
        delete issueOrders;
        delete executeOrders;
        delete win;
        startState, mapLoadedState, mapValidated, playersAdded, assignReinforcement, issueOrders, executeOrders, win = NULL;
    }; 

    // function that handles changing states
    void changeState(GameState* newState);
    
    // function which is responsible for receiving the user's command and then delegating it to the current state
    void handleCommand(const std::string& command);

    // getters for the different states
    GameState* getStartState() { return startState; }
    GameState* getMapLoadedState() { return mapLoadedState; }
    GameState* getMapValidated() { return mapValidated; }
    GameState* getPlayersAdded() { return playersAdded; }
    GameState* getAssignReinforcement() { return assignReinforcement; }
    GameState* getIssueOrders() { return issueOrders; }
    GameState* getExecuteOrders() { return executeOrders; }
    GameState* getWin() { return win; }

private:
    // declaring instances of the states and a pointer that points to the current state
    GameState* currentState;
    GameState* startState;
    GameState* mapLoadedState;
    GameState* mapValidated;
    GameState* playersAdded;
    GameState* assignReinforcement;
    GameState* issueOrders;
    GameState* executeOrders;
    GameState* win;
};

// to parse user input and map it to specific commands accepted by the GameEngine
class CommandParser {
public:
    // contructor of the class and member initializer list → initlializes pointer that points to GameEngine object
    CommandParser(GameEngine* engine) : engine(engine) {}

    //copy constructor
    CommandParser(const CommandParser& commandParser){};

    //destructor
    virtual ~CommandParser(){}
    
    // all the accepted commands
    vector<string> commands{"loadmap", "validatemap", "addplayer", "assigncountries", "issueorder", "endissueorders", "execorder", "endexecorders", "win", "play", "end"};
    
    // function to process string inputs
    void parseCommand(const std::string& input);

private:
    GameEngine* engine;
};


#endif