#include "GameEngine.h"

// creating a list of game states
const char *GameEngine::GameStateStrings[] = {
    "startState",
    "mapLoadedState",
    "mapValidated",
    "playersAdded",
    "assignReinforcement",
    "issueOrders",
    "executeOrders",
    "win"};

// defining the GameEngine constructor, creating the state transition map which maps commands to the states they transition to
GameEngine::GameEngine(Observer* o) : currentState(GameStateStrings[0])
{
    Attach(o);
    stateTransitionMap.insert(pair<std::string, const char *>("loadmap", GameStateStrings[1]));
    stateTransitionMap.insert(pair<std::string, const char *>("validatemap", GameStateStrings[2]));
    stateTransitionMap.insert(pair<std::string, const char *>("addplayer", GameStateStrings[3]));
    stateTransitionMap.insert(pair<std::string, const char *>("gamestart", GameStateStrings[4]));
    stateTransitionMap.insert(pair<std::string, const char *>("replay", GameStateStrings[0]));
};


// defining the copy constructor
GameEngine::GameEngine(const GameEngine &game_engine)
{
    std::cout << "Copy Constructor of GameEngine";
};

// defining the destructor
GameEngine::~GameEngine()
{
    delete commandProcessor;
    commandProcessor = NULL;
};

// function to get the current state
const char *GameEngine::getCurrentState()
{
    return currentState;
}

// function to handle state transitions, it finds the command in the map and changes the state associated with it
void GameEngine::stateTransition(Command *cmd)
{
    std::string command = cmd->getCommandStr();

    if (stateTransitionMap.find(command) != stateTransitionMap.end())
    {
        currentState = stateTransitionMap.find(command)->second;
        cmd->saveEffect(currentState);
        std::cout << "Changing state to: " << currentState << "...\n"
                  << std::endl;
    }
 //    Notify(this);
}

std::string GameEngine::stringToLog()
{
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
	//CommandProcessor *commandProcessor = nullptr;
	FileLineReader *fileLineReader = nullptr;
	Map *mapP = nullptr;
	int nbPlayers = 0;
	std::string fileName;
	std::ifstream file;
	vector<Player> players;

	if (inputMode == "1") {
		commandProcessor = new CommandProcessor();
        commandProcessor -> Attach(observer);
		useConsole = true;
	}
	else if (inputMode == "2") {
		std::cout << "\nEnter the file name: ";
		std::cin >> fileName;
		commandProcessor = new FileCommandProcessorAdapter(fileLineReader);
        commandProcessor -> Attach(observer);
		file.open(fileName);
		useFile = true;
	}

	else {
		std::cerr << "\nInvalid input mode. Exiting..." << std::endl;
		return;
	}

	GameEngine engine = GameEngine(observer);
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
					bool isValidatedMap = Map::validate(mapP);
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
						players.push_back(Player(observer,argument)); // Add player with the specified name
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
			bool isRightCommand = engine.processFileCommand(command, commandProcessor);
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
					bool isValidatedMap = Map::validate(mapP);
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
						players.push_back(Player(observer,argument)); // Add player with the specified name
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
// added Main Game Loop part of the game
void GameEngine::reinforcementPhase(vector<Player *> v, Map *map)
{
    int armies = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i]->getTerritories().size() < 9)
        {
            armies = 3;
            v[i]->setReinforcementPool(armies);
        }
        else
        {
            armies = v[i]->getTerritories().size() / 3;
        }

        cout << v[i]->getPlayerName() << " originally has " << armies << " armies" << endl;
        for (Continent *c : map->getContinents())
        {
            int count = 0;
            for (int n = 0; n < v[i]->getTerritories().size(); n++)
            {
                for (Territory *t : c->getTerritories())
                {
                    if (t->getName().compare(v[i]->getTerritories()[n]->getName()) == 0)
                    {
                        count++;
                    }
                }
            }
            if (count == c->getTerritories().size())
            {
                armies += static_cast<int>(std::floor(c->getBonus()));
                cout << v[i]->getPlayerName() << " has concurred continent: " << c->getName() << "\nbonus added for that continent: " << c->getBonus() << endl;
                cout << v[i]->getPlayerName() << " now has " << armies << " armies after bonus of " << c->getBonus() << "\n"
                     << endl;
            }
        }
        v[i]->setReinforcementPool(armies);
    }
}

// everything works except for the commented part !!!
void GameEngine::issueOrdersPhase(vector<Player *> v)
{
    // vector to keep track of the count of each player for the Advance order
    // this is done so that the advance order is done a maximum of 3 times
    // each box from this vector is of each player and represents the number of times they advanced
    vector<int> countAdvanceTerritories(v.size());

    // vector to keep track of the index of each player for their Hand vector
    // this is done so that the other order types from their hand can be
    // kept track and used
    // each box from this vector is of each player and represents the player's index in their vector cardsAtHand
    vector<int> indexHandVector(v.size());

    // vector to keep track of all the players that does not have any more orders
    // each box will either have a value of 0 or 1
    // 0 represents the fact that there are still orders left
    // 1 represents the fact that there are no more orders left
    // if every value in the vector is 1, then no more orders for the player
    vector<int> outOfOrder(v.size());

    // boolean moreOrder to continue this loop until there are no more orders
    bool moreOrder = true;
    while (moreOrder)
    {
        // a count that determines the number of players that does not have any more orders
        int countDone = 0;

        // go through the vector of players
        for (int i = 0; i < v.size(); i++)
        {
            // if the player still has armies in reinforcement, deploy order
            // temp is used to avoid modifying the original reinforcement pool values until order execution
            if (v[i]->getReinforcementTemp() != 0)
            {
                Deploy *d = new Deploy();
                v[i]->issueOrder(d);
                // cout << "remaining armies for " << v[i]->getPlayerName() << " " << v[i]->getReinforcementTemp() << endl;
                continue;
            }

            // the player is allowed to advance order a maximum of 3 times, else move to the next
            else if (countAdvanceTerritories[i] != 3)
            {
                Advance *a = new Advance();
                v[i]->issueOrder(a);

                countAdvanceTerritories[i]++;
                // cout << "count for " << v[i]->getPlayerName() << " for advance " << countAdvanceTerritories[i] << endl;
                continue;
            }

            // // if it arrives at the end of the player's cardsInHand array, skip this statement
            else if (v[i]->getHand()->cardsInHand.size() != 0 && indexHandVector[i] != v[i]->getHand()->cardsInHand.size())
            {
                if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Bomb") == 0)
                {
                    Bomb *b = new Bomb();
                    v[i]->issueOrder(b);
                }

                if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Negotiate") == 0)
                {
                    Negotiate *n = new Negotiate();
                    v[i]->issueOrder(n);
                }

                if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Blockade") == 0)
                {
                    Blockade *b = new Blockade();
                    v[i]->issueOrder(b);
                }

                if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Airlift") == 0)
                {
                    Airlift *a = new Airlift();
                    v[i]->issueOrder(a);
                }

                indexHandVector[i]++;
                continue;
            }

            // when all of the previous possible orders are done, change the value to 1 for that player
            else if (outOfOrder[i] != 1)
            {
                outOfOrder[i] = 1;
            }
        }

        // calculate the total number of players that are done
        // if the countDone is equal to the number of players, end the loop (no more orders) !
        for (int j : outOfOrder)
        {
            if (outOfOrder[j] == 1)
            {
                countDone++;
            }
        }

        // if all players are done, the loop is done !
        if (countDone == v.size())
        {
            moreOrder = false;
        }
    }
    // checks all the orders of the players:

    // for (int i = 0; i < v[0]->getOrderList()->getOrders().size(); i++)
    // {
    //     cout << v[0]->getPlayerName() << endl;
    //     cout << *(v[0]->getOrderList()->getOrders()[i]) << endl;
    // }

    // for (int i = 0; i < v[1]->getOrderList()->getOrders().size(); i++)
    // {
    //     cout << v[1]->getPlayerName() << endl;
    //     cout << *(v[1]->getOrderList()->getOrders()[i]) << endl;
    // }
}

void GameEngine::executeOrdersPhase(vector<Player *> v)
{

    // vector to keep track of the index of each player for their OrderList vector
    // this is done so that the orders from their OrderList can be kept track and used
    // each box from this vector is of each player and represents the player's index in their vector orders->getOrders() vector
    vector<int> indexOrderList(v.size());

    // vector to keep track of all the players that does not have any more orders to execute
    // each box will either have a value of 0 or 1
    // 0 represents the fact that there are still orders left
    // 1 represents the fact that there are no more orders left
    // if every value in the vector is 1, then no more orders for the player
    vector<int> outOfOrder(v.size());

    // boolean moreOrder to continue this loop until there are no more orders
    bool moreOrder = true;
    while (moreOrder)
    {
        // a counter that keeps track of the number of players that are done
        int countDone = 0;
        // go through the vector of players
        for (int i = 0; i < v.size(); i++)
        {
            // if it arrives at the end of the orders list for the player, skip this statement
            if (indexOrderList[i] != v[i]->getOrderList()->getOrders().size())
            {
                v[i]->getOrderList()->getOrders()[indexOrderList[i]]->execute();
                indexOrderList[i]++;
            }
            // when all of the previous possible orders are done, change the value to 1 for that player
            else if (outOfOrder[i] != 1)
            {
                outOfOrder[i] = 1;
            }
        }
        // calculate the total number of players that are done
        // of the countDone is equal to the number of players, end the loop (no more orders) !
        for (int j = 0; j < outOfOrder.size(); j++)
        {
            if (outOfOrder[j] == 1)
                countDone++;
        }
        // if all players are done, the loop is done !
        if (countDone == v.size())
        {
            cout << "\ndone with all executions !" << endl;
            moreOrder = false;
        }
    }
}
void GameEngine::mainGameLoop(vector<Player *> v, Map *map)
{
    bool noWinner = true;
    do
    {
        reinforcementPhase(v, map);
        issueOrdersPhase(v);
        executeOrdersPhase(v);

        for (int i; i < v.size(); i++)
        {
            if (v[i]->getTerritories().size() == 0)
            {
                v.erase(v.begin() + i);
            }
        }

        if (v.size() == 1)
        {
            noWinner = false;
        }
    } while (noWinner);

    string answer;
    cout << "Winner ! Player: " << v[0]->getPlayerName() << endl;
    cout << "\nWould you like to play again ?\n<replay> if you want to replay !\n<quit> if you want to end the game..." << endl;
    cin >> answer;
}
