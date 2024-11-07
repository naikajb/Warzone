#include <vector>
#include <algorithm>
#include <random>
#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

using namespace std;

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
    
    stateTransitionMap.insert(pair<string, const char*>("loadmap", GameStateStrings[1]));
    stateTransitionMap.insert(pair<string, const char*>("validatemap", GameStateStrings[2]));
    stateTransitionMap.insert(pair<string, const char*>("addplayer", GameStateStrings[3]));
    stateTransitionMap.insert(pair<string, const char*>("gamestart", GameStateStrings[4]));
    stateTransitionMap.insert(pair<string, const char*>("replay", GameStateStrings[0]));
};


//defining the copy constructor
GameEngine::GameEngine(const GameEngine& game_engine) {
    cout << "Copy Constructor of GameEngine";
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
    string command = cmd->getCommandStr();

    if (stateTransitionMap.find(command) != stateTransitionMap.end()) {
        currentState = stateTransitionMap.find(command)->second;
        cmd->saveEffect(currentState);
        cout << "Changing state to: " << currentState << "...\n" << endl;
    }
       Notify(this);
}

string GameEngine::stringToLog() {
    return "GameEngine changed state to " + string(currentState);
}

//function to process commands entered by the user
void GameEngine::processCommand(string& command) {
   
    Command* cmd = commandProcessor->getCommand(command);

    cout << "\nCurrent State: " << getCurrentState() << "\n" << endl;

    if((commandProcessor->validate(cmd, this->getCurrentState())) == true) {
        stateTransition(cmd);
        
    } else {
        cout << "Invalid command. Try again.\n" << endl;

    };
}

void GameEngine::startupPhase() {
    cout<<"Welcome to Warzone! 💣🌎💣🗺️💣🌎🏆🗺️" <<endl;
    //cout<<"Enter a command: " <<endl;
    cout<<"Enter the name of the file: ";
    string filename;
    cin>> filename ;
    MapLoader ml(filename);
    //Map object of the map from the filename
    Map *mapP = ml.getMap();
    
    bool isValidatedMap = mapP->validate;

    if (isValidatedMap){
        cout<<"Hooray!🎉🎉 file has a valid map!🗺️🗺️"<<endl;
        //use the addplayer <playername> command to enter players in the game (2-6 players)
        cout<<"Please enter the number of players: ";
        int nbPlayers;
        cin>>nbPlayers;
        
        vector<Player> players;
        
        for (int i=0; i<nbPlayers;i++){
            string name; 
            cout<<"Please enter the name of player "<<i<<endl;
            cin>>name;
            players[i]=Player(name);

        }

        //Distrribute the territories to each player 
        vector<Territory *> allTerritories = mapP->getTerritories();
        int nbTerritories = allTerritories.size();
        
        vector<int> randomOrder = getRandomizedNumbers(nbTerritories);
        
        //Assign an equal number of territories to each player 
        for (int i=0; i<nbTerritories; i++){
            for (int j=0; j<nbPlayers; j++){
                for (int k=0; k<(nbTerritories/nbPlayers);k++){
                    players[j].addTerritory(allTerritories[randomOrder[i]]);
                }
            }  
        }

        //Determine randomly the order of play of the players in the game
        vector<int> playersOrder = getRandomizedNumbers(nbPlayers);

        Deck deck;

        //let each player draw 2 initial cards from the deck using the deck’s draw() method
        for (int i=0; i<players.size();i++){
            players[playersOrder[i]].addCard(deck.draw());
            players[playersOrder[i]].addCard(deck.draw());
        }
         
        //switch the game to the play phase

    }
    else {
        cout<<"Invalid map! ❌"<<endl;
    }
}

vector<int> getRandomizedNumbers(int n) {
    // Step 1: Create a vector with numbers from 0 to n-1
    vector<int> randomizedNumbers;
    for (int i = 0; i < n; ++i) {
        randomizedNumbers.push_back(i);
    }

    // Step 2: Shuffle the vector randomly
    random_device rd;
    mt19937 generator(rd());
    shuffle(randomizedNumbers.begin(), randomizedNumbers.end(), generator);

    return randomizedNumbers;
}


