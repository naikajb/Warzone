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
    //declaring default constructor
    GameState();

    //declaring copy constructor
    GameState(const GameState& gameState);

    //declaring destructor
    virtual ~GameState();

    //pure virtual functions, they are abstract (=0) and must be overriden by the derived classes
    virtual void handleCommand(GameEngine* engine, const std::string& command) = 0;
    virtual std::string getStateName() = 0; 
};

// derived class which represents one of the different states of the Game Engine
class StartState : public GameState {
public:
    StartState();
    StartState(const StartState& startState);
    virtual ~StartState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class MapLoadedState : public GameState {
public: 
    MapLoadedState();
    MapLoadedState(const MapLoadedState& mapLoadedState);
    virtual ~MapLoadedState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class MapValidatedState : public GameState {
public:
    MapValidatedState();
    MapValidatedState(const MapValidatedState& mapValidatedState);
    virtual ~MapValidatedState();
    void handleCommand(GameEngine* engine, const std::string& command) override;

    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class PlayersAddedState : public GameState {
public:
    PlayersAddedState();
    PlayersAddedState(const PlayersAddedState& PlayersAddedState);
    virtual ~PlayersAddedState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class AssignReinforcementState : public GameState {
public:
    AssignReinforcementState();
    AssignReinforcementState(const AssignReinforcementState& assignReinf);
    virtual ~AssignReinforcementState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class IssueOrdersState : public GameState {
public:
    IssueOrdersState();
    IssueOrdersState(const IssueOrdersState& issueOrderState);
    virtual ~IssueOrdersState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
}; 

class ExecuteOrdersState : public GameState {
public:
    ExecuteOrdersState();
    ExecuteOrdersState(const ExecuteOrdersState& executeOrderState);
    virtual ~ExecuteOrdersState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

class WinState : public GameState {
public:
    WinState();
    WinState(const WinState& winState);
    virtual ~WinState();
    void handleCommand(GameEngine* engine, const std::string& command) override;
    std::string getStateName() override;

private: 
    GameEngine* engine;
};

// GameEngine class which manages the current state and provides a function to switch between states
class GameEngine {
public:
    // declaring constructor
    GameEngine();

    // copy constructor
    GameEngine(const GameEngine& game_engine);

    // destructor
    virtual ~GameEngine();

    // function that handles changing states
    void changeState(GameState* newState);
    
    // function which is responsible for receiving the user's command and then delegating it to the current state
    void handleCommand(const std::string& command);

    // declaring getters for the different states 
    GameState* getStartState();
    GameState* getMapLoadedState();
    GameState* getMapValidated();
    GameState* getPlayersAdded();
    GameState* getAssignReinforcement();
    GameState* getIssueOrders();
    GameState* getExecuteOrders();
    GameState* getWin();

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
    CommandParser(GameEngine* engine);

    //copy constructor
    CommandParser(const CommandParser& commandParser);

    //destructor
    virtual ~CommandParser();
    
    // vector that stores all the accepted commands
    vector<string> commands{"loadmap", "validatemap", "addplayer", "assigncountries", "issueorder", "endissueorders", "execorder", "endexecorders", "win", "play", "end"};
    
    // function to process string inputs
    void parseCommand(const std::string& input);

private:
    GameEngine* engine;
};

void testGameStates();


#endif