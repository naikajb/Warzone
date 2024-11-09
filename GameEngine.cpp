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
bool GameEngine::processConsoleCommand(std::string& command, CommandProcessor* commandProcessor) {

    Command* cmd = commandProcessor->getCommand(command);
    std::cout << "\nCurrent State: " << getCurrentState() << "\n" << std::endl;
    if((commandProcessor->validate(cmd, this->getCurrentState())) == true) {
        stateTransition(cmd); //command is good
        return true;
    } else {
        std::cout << "Invalid command. Try again.\n" << std::endl;
        return false;
    }
};

//function to process file commands 
bool GameEngine::processFileCommand(std::string& command, CommandProcessor* commandProcessor) {

    Command* cmd = nullptr;
    while ((cmd = commandProcessor->getCommand(command)) != nullptr) {
        std::cout << "\nCurrent State: " << getCurrentState() << "\n" << std::endl;
        if((commandProcessor->validate(cmd, this->getCurrentState())) == true) {
            stateTransition(cmd);
            return true;
        } else {
            std::cout << "Invalid command. Try again.\n" << std::endl;
            return false;
        }
    }   
    std::cout << "\nNo more commands to process.\nCurrent State: " << getCurrentState() << "\n" << std::endl;
    delete cmd;
    exit(0);
}

void GameEngine::startupPhase()
{
	std::string inputMode;
	bool useConsole = false;
	bool useFile = false;
	std::cout << "Welcome to the Game Engine!\n\n"
			  << "Choose a mode to input commands: \n"
			  << "1. Console\n"
			  << "2. File\n"
			  << "\nEnter 1 or 2:\n"
			  << "> ";
	std::cin >> inputMode;
	CommandProcessor *commandProcessor = nullptr;
	FileLineReader *fileLineReader = nullptr;
	Map *mapP = nullptr;
	int nbPlayers = 0;
	std::string fileName;
	std::ifstream file;
	vector<Player> players;

	if (inputMode == "1") {
		commandProcessor = new CommandProcessor();
		useConsole = true;
	}
	else if (inputMode == "2") {
		std::cout << "\nEnter the file name: ";
		std::cin >> fileName;
		commandProcessor = new CommandProcessor();
		file.open(fileName);
		useFile = true;
	}

	else {
		std::cerr << "\nInvalid input mode. Exiting..." << std::endl;
		return;
	}

	GameEngine engine;
	std::cout << "\nStarting Game Engine\n\n";

	std::string input;
	std::string unknown = "";

	if (useConsole)
	{
		while (true)
		{
			std::cout << "Type a command " << std::endl;
			std::cout << "> ";
			std::getline(std::cin >> std::ws, input);

			// Split command and argument
			std::istringstream iss(input);
			std::string command, argument;
			iss >> command;
			std::getline(iss >> std::ws, argument);
			bool isRightCommand = engine.processConsoleCommand(command, commandProcessor);
			if (isRightCommand)
			{
				if (command == "loadmap")
				{
					MapLoader ml(argument);
					// Map object of the map from the filename
					mapP = ml.getMap();
					std::cout << "Map loaded successfully!" << std::endl;
				}
				else if (command == "validatemap")
				{
					bool isValidatedMap = mapP->validate;
					if (isValidatedMap)
					{
						std::cout << "Map is validated!" << std::endl;
					}
					else
					{
						std::cout << "Map is not validated!" << std::endl;
					}
				}
				else if (command == "addplayer")
				{
					if (argument != "")
					{
						players.push_back(Player(argument)); // Add player with the specified name
						nbPlayers++;
						std::cout << "Player " << argument << " added successfully!" << std::endl;
					}
					else
					{
						std::cout << "Error: addplayer command requires a <playername> argument." << std::endl;
					}
				}
				else if (command == "gamestart")
				{
					if (nbPlayers >= 2 && nbPlayers <= 6)
					{
						// Distrribute the territories to each player
						vector<Territory *> allTerritories = mapP->getTerritories();
						int nbTerritories = allTerritories.size();

						vector<int> randomOrder = getRandomizedNumbers(nbTerritories);

						// Assign an equal number of territories to each player
						for (int i = 0; i < nbTerritories; i++)
						{
							for (int j = 0; j < nbPlayers; j++)
							{
								for (int k = 0; k < (nbTerritories / nbPlayers); k++)
								{
									players[j].addTerritory(allTerritories[randomOrder[i]]);
								}
							}
						}

						// Determine randomly the order of play of the players in the game
						vector<int> playersOrder = getRandomizedNumbers(nbPlayers);

						Deck deck;

						// let each player draw 2 initial cards from the deck using the deck’s draw() method
						for (int i = 0; i < players.size(); i++)
						{
							players[playersOrder[i]].addCard(deck.draw());
							players[playersOrder[i]].addCard(deck.draw());
						}
					}
					else
					{
						std::cout << "Error: Number of players must be between 2 and 6." << std::endl;
						std::cout << "Exiting system ..." << std::endl;
						exit(0);
					}
				}
			}

			if (command == "exit")
			{
				break;
			}
		}
	}

	if (useFile)
	{
		std::string line = "";
		while (getline(file, line))
		{
			// Split command and argument
			std::istringstream iss(line);
			std::string command, argument;
			iss >> command;
			std::getline(iss >> std::ws, argument);
			bool isRightCommand = engine.processConsoleCommand(command, commandProcessor);
			if (isRightCommand)
			{
				if (command == "loadmap")
				{
					MapLoader ml(argument);
					// Map object of the map from the filename
					mapP = ml.getMap();
					std::cout << "Map " << argument << " loaded successfully!" << std::endl;
				}
				else if (command == "validatemap")
				{
					bool isValidatedMap = mapP->validate;
					if (isValidatedMap)
					{
						std::cout << "Map is validated!" << std::endl;
					}
					else
					{
						std::cout << "Map is not validated!" << std::endl;
					}
				}
				else if (command == "addplayer")
				{
					if (argument != "")
					{
						players.push_back(Player(argument)); // Add player with the specified name
						nbPlayers++;
						std::cout << "Player " << argument << " added successfully!" << std::endl;
					}
					else
					{
						std::cout << "Error: addplayer command requires a <playername> argument." << std::endl;
					}
				}
				else if (command == "gamestart")
				{

					if (nbPlayers >= 2 && nbPlayers <= 6)
					{
						// Distrribute the territories to each player
						vector<Territory *> allTerritories = mapP->getTerritories();
						int nbTerritories = allTerritories.size();

						vector<int> randomOrder = getRandomizedNumbers(nbTerritories);

						// Assign an equal number of territories to each player
						for (int i = 0; i < nbTerritories; i++)
						{
							for (int j = 0; j < nbPlayers; j++)
							{
								for (int k = 0; k < (nbTerritories / nbPlayers); k++)
								{
									players[j].addTerritory(allTerritories[randomOrder[i]]);
								}
							}
						}

						// Determine randomly the order of play of the players in the game
						vector<int> playersOrder = getRandomizedNumbers(nbPlayers);

						Deck deck;

						// let each player draw 2 initial cards from the deck using the deck’s draw() method
						for (int i = 0; i < players.size(); i++)
						{
							players[playersOrder[i]].addCard(deck.draw());
							players[playersOrder[i]].addCard(deck.draw());
						}
					}
					else
					{
						std::cout << "Error: Number of players must be between 2 and 6." << std::endl;
						std::cout << "Exiting system ..." << std::endl;
						exit(0);
					}
				}
			}
		}
	}

	delete commandProcessor;
	delete fileLineReader;
	commandProcessor = nullptr;
	fileLineReader = nullptr;
}

vector<int> GameEngine::getRandomizedNumbers(int n)
{
	// Step 1: Create a vector with numbers from 0 to n-1
	vector<int> randomizedNumbers;
	for (int i = 0; i < n; ++i)
	{
		randomizedNumbers.push_back(i);
	}

	// Step 2: Shuffle the vector randomly
	random_device rd;
	mt19937 generator(rd());
	shuffle(randomizedNumbers.begin(), randomizedNumbers.end(), generator);

	return randomizedNumbers;
}
