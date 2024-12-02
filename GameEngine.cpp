#include "GameEngine.h"
#include "Player.h"
// g++ *.cpp -o program.exe

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
GameEngine::GameEngine(Observer *o) : currentState(GameStateStrings[0])
{
    Attach(o);
    observer = o;
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
GameEngine::~GameEngine() {
    // if (observer) {
    //     delete observer;
    //     observer = nullptr;
    // }
    // delete commandProcessor;
    // commandProcessor = NULL;
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
    Notify(this);
}

std::string GameEngine::stringToLog()
{
    return "GameEngine changed state to " + std::string(currentState);
}

// function to process console commands
bool GameEngine::processConsoleCommand(std::string &command, CommandProcessor *commandProcessor)
{

    Command *cmd = commandProcessor->getCommand(command);
    std::cout << "\nCurrent State: " << getCurrentState() << "\n"
              << std::endl;
    if ((commandProcessor->validate(cmd, this->getCurrentState())) == true)
    {
        stateTransition(cmd); // command is good
        return true;
    }
    else
    {
        std::cout << "Invalid command. Try again.\n"
                  << std::endl;
        return false;
    }
};

// function to process file commands
bool GameEngine::processFileCommand(std::string &command, CommandProcessor *commandProcessor)
{

    Command *cmd = nullptr;
    while ((cmd = commandProcessor->getCommand(command)) != nullptr)
    {
        std::cout << "\nCurrent State: " << getCurrentState() << "\n"
                  << std::endl;
        if ((commandProcessor->validate(cmd, this->getCurrentState())) == true)
        {
            stateTransition(cmd);
            return true;
        }
        else
        {
            std::cout << "Invalid command. Try again.\n"
                      << std::endl;
            return false;
        }
    }
    std::cout << "\nNo more commands to process.\nCurrent State: " << getCurrentState() << "\n"
              << std::endl;
    delete cmd;
    exit(0);
}

// function to process console or file commands
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

    // command processor for console commands
    CommandProcessor *commandProcessor = nullptr;
    // command processor for file commands
    CommandProcessor *commandP = nullptr;

    FileLineReader *fileLineReader = nullptr;
    Map *mapP = nullptr;
    int nbPlayers = 0;
    std::string fileName;
    std::ifstream file;
    vector<Player *> players;

    if (inputMode == "1")
    {
        commandProcessor = new CommandProcessor(observer);
        useConsole = true;
    }
    else if (inputMode == "2")
    {
        useFile = true;
        while (true)
        {
            std::cout << "\nEnter the file name: ";
            std::cin >> fileName;
            try
            {
                fileLineReader = new FileLineReader(fileName);
                commandProcessor = new FileCommandProcessorAdapter(observer, fileLineReader);
                break;
            }
            catch (std::invalid_argument &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    else
    {
        std::cerr << "\nInvalid input mode. Exiting..." << std::endl;
        return;
    }

    std::cout << "\nStarting Game Engine\n\n";
    GameEngine engine = GameEngine(observer);

    std::cout << "\nStarting Game Engine\n\n";

    std::string input;
    std::string unknown = "";

    // if (useConsole)
    // {
    while (useConsole)
    {
        auto it = this->getCurrentState();
        std::string currentStateStr(it);
        commandProcessor->displayCommands(currentStateStr);
        std::cout << "> ";
        std::getline(std::cin >> std::ws, input);

        // Split command and argument
        std::istringstream iss(input);
        std::string command, argument;
        iss >> command;
        std::getline(iss >> std::ws, argument);

        Command *cmd = commandProcessor->getCommand(command);
        std::cout << "\nCurrent State: " << getCurrentState() << "\n"
                  << std::endl;

        // bool isRightCommand = engine.processConsoleCommand(command, commandProcessor);
        // Command* cmd = commandProcessor->getCommand(command);

        if (input == "exit")
        {
            std::cout << "Exiting startup phase and returning to menu...\n\n";
            break;
        }

        if ((commandProcessor->validate(cmd, this->getCurrentState())) == true)
        {

            if (command == "loadmap")
            {

                std::cout << "Loading map from: " << argument << std::endl;

                MapLoader *ml = new MapLoader(argument);

                // Map object of the map from the filename
                mapP = ml->getMap();

                if (mapP != nullptr)
                {
                    std::cout << "Map loaded successfully!" << std::endl;
                    stateTransition(cmd);
                    continue;
                }
                else
                {
                    std::cout << "Error: Map failed to load." << std::endl;
                }

                delete ml;
                ml = nullptr;
            }
            else if (command == "validatemap")
            {

                std::cout << *mapP << std::endl;

                bool isValidatedMap = Map::validate(mapP);

                if (isValidatedMap)
                {
                    std::cout << "Map is validated!" << std::endl;
                    stateTransition(cmd);
                    continue;
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
                    Player *p = new Player(observer, argument);
                    players.push_back(p); // Add player with the specified name
                    nbPlayers++;
                    std::cout << "Player " << argument << " added successfully!" << std::endl;
                    stateTransition(cmd);
                    continue;
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

                    stateTransition(cmd);

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
                                players[j]->addTerritory(allTerritories[randomOrder[i]]);
                            }
                        }
                    }

                    // Determine randomly the order of play of the players in the game
                    vector<int> playersOrder = getRandomizedNumbers(nbPlayers);

                    Deck deck;

                    setupPlayers(players);

                    // let each player draw 2 initial cards from the deck using the deck’s draw() method
                    for (int i = 0; i < players.size(); i++)
                    {
                        players[playersOrder[i]]->addCard(deck.draw());
                        players[playersOrder[i]]->addCard(deck.draw());
                    }

                    engine.mainGameLoop(players, mapP);
                }
                else
                {
                    std::cout << "Error: Number of players must be between 2 and 6." << std::endl;
                    std::cout << "Exiting system ..." << std::endl;
                    exit(0);
                }
            }
            else if (command == "replay")
            {
                stateTransition(cmd);
                continue;
            }
            else if (command == "quit")
            {
                exit(0);
            }
        }
        else
        {
            std::cout << "Invalid command. Try again.\n"
                      << std::endl;
        }
    }
    // }

    if (useFile)
    {
        std::string cmmd = "";
        CommandProcessor *commandP = new CommandProcessor(observer);

        Command *cmd = nullptr;
        Command *fileC = nullptr;

        while ((cmd = commandProcessor->getCommand(cmmd)) != nullptr)
        {
            std::cout << "\nCurrent State: " << getCurrentState() << "\n"
                      << std::endl;
            std::string commandStr = cmd->getCommandStr();
            std::istringstream stream(commandStr);
            std::string command;
            std::string argument;

            stream >> command;
            std::getline(stream >> std::ws, argument);

            fileC = commandP->getCommand(command);

            if ((commandProcessor->validate(fileC, this->getCurrentState())) == true)
            {

                if (command == "loadmap")
                {

                    std::cout << "Loading map from: " << argument << std::endl;

                    MapLoader *ml = new MapLoader(argument);
                    // Map object of the map from the filename
                    mapP = ml->getMap();
                    if (mapP != nullptr)
                    {
                        std::cout << "Map loaded successfully!" << std::endl;
                        stateTransition(fileC);
                        continue;
                    }
                    else
                    {
                        std::cout << "Error: Map failed to load." << std::endl;
                    }
                    delete ml;
                    ml = nullptr;
                }
                else if (command == "validatemap")
                {
                    std::cout << *mapP << std::endl;
                    MapLoader *ml = new MapLoader(argument);
                    // Map object of the map from the filename
                    mapP = ml->getMap();
                    if (mapP != nullptr)
                    {
                        std::cout << "Map loaded successfully!" << std::endl;
                        stateTransition(fileC);
                        continue;
                    }
                    else
                    {
                        std::cout << "Error: Map failed to load." << std::endl;
                    }
                    delete ml;
                    ml = nullptr;
                }
                else if (command == "addplayer")
                {
                    if (argument != "")
                    {
                        Player *pf = new Player(observer, argument);
                        players.push_back(pf); // Add player with the specified name
                        nbPlayers++;
                        std::cout << "Player " << argument << " added successfully!" << std::endl;
                        stateTransition(fileC);
                        continue;
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
                        stateTransition(fileC);
                        // Distrribute the territories to each player
                        vector<Territory *> allTerritories = mapP->getTerritories();
                        int nbTerritories = allTerritories.size();
                        if (nbPlayers >= 2 && nbPlayers <= 6)
                        {
                            stateTransition(fileC);
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
                                        players[j]->addTerritory(allTerritories[randomOrder[i]]);
                                    }
                                }
                            }

                            // Determine randomly the order of play of the players in the game
                            vector<int> playersOrder = getRandomizedNumbers(nbPlayers);

                            Deck deck;

                            // let each player draw 2 initial cards from the deck using the deck’s draw() method
                            for (int i = 0; i < players.size(); i++)
                            {
                                players[playersOrder[i]]->addCard(deck.draw());
                                players[playersOrder[i]]->addCard(deck.draw());
                            }

                            engine.mainGameLoop(players, mapP);
                        }
                        else
                        {
                            std::cout << "Error: Number of players must be between 2 and 6." << std::endl;
                            std::cout << "Exiting system ..." << std::endl;
                            exit(0);
                        }
                    }
                    else if (command == "replay")
                    {
                        stateTransition(fileC);
                        continue;
                    }
                    else if (command == "quit")
                    {
                        exit(0);
                    }
                }
                else
                {
                    std::cout << "Invalid command. Try again.\n"
                              << std::endl;
                }
            }
            std::cout << "\nNo more commands to process.\nCurrent State: " << getCurrentState() << "\n"
                      << std::endl;
            delete commandP;
            commandP = nullptr;
            exit(0);
        }

        delete commandProcessor;
        delete fileLineReader;
        commandProcessor = nullptr;
        fileLineReader = nullptr;
    }
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

void GameEngine::setupPlayers(std::vector<Player *> &players)
{
    Player::assignStrategies(players); // Call the static function
}

// added Main Game Loop part of the game
void GameEngine::reinforcementPhase(vector<Player *> v, Map *map, int round)
{
    cout << "\n~~~~~~REINFORCEMENT PHASE~~~~~~\n"
         << endl;
    int armies = 0;

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i]->getPlayerName() << " has concurred " << v[i]->getTerritories().size() << " territories total !\n"
             << endl;

        for (Territory *t : v[i]->getTerritories())
        {
            cout << t->getName() << " -> with armies " << t->getNumArmies() << endl;
        }
        cout << "\n";
        if (v[i]->getTerritories().size() < 9)
        {
            armies = 3;
            v[i]->setReinforcementPool(armies);
        }
        else
        {
            armies = v[i]->getTerritories().size() / 3;
        }

        cout << v[i]->getPlayerName() << " has " << armies << " armies before any bonus" << endl;
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

void GameEngine::issueOrdersPhase(vector<Player *> v, int round)
{
    cout << "\n~~~~~~ISSUE ORDERING PHASE~~~~~~\n"
         << endl;

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

    // empties list of orders at the start of every round
    for (Player *p : v)
    {
        // might change so that it saves the drawn card from the advance
        p->getOrderList()->clearOrders();
        // if (p->getPlayerStrategy()->getPlayerType() == "Cheater"){

        // }
    }
    resetNegotiatePairs();

    int cheaterCount = 0;

    // add a loop that checks for the neutral player, and remove all its orders and cards at the start of the game

    // boolean moreOrder to continue this loop until there are no more orders
    bool moreOrder = true;
    while (moreOrder)
    {
        // a count that determines the number of players that does not have any more orders
        int countDone = 0;

        // go through the vector of players
        for (int i = 0; i < v.size(); i++)
        {

            // if(v[i]->getPlayerStrategy()->getPlayerType() == "Human"){

            //     Order* d = new Deploy();
            //     v[i]->issueOrder(d);
            //     continue;

            if (v[i]->getPlayerStrategy()->getPlayerType() == "Cheater" && cheaterCount != 1 && round != 1)
            {
                Advance *a = new Advance();
                v[i]->issueOrder(a);

                if (outOfOrder[i] != 1)
                {
                    cout << "\n"
                         << v[i]->getPlayerName() << " is a " << v[i]->getPlayerStrategy()->getPlayerType() << " player and is about to cheat ! out of orders !" << endl;
                    outOfOrder[i] = 1;
                }
                cheaterCount++;
                continue;
            }

            if (v[i]->getPlayerStrategy()->getPlayerType() == "Neutral" && round != 1)
            {
                if (outOfOrder[i] != 1)
                {
                    cout << "\n"
                         << v[i]->getPlayerName() << " is a " << v[i]->getPlayerStrategy()->getPlayerType() << " player and does not make any orders ! out of orders !" << endl;
                    outOfOrder[i] = 1;
                }
                continue;
            }

            // if the player still has armies in reinforcement, deploy order
            // temp is used to avoid modifying the original reinforcement pool values until order execution
            if (v[i]->getReinforcementTemp() != 0 && v[i]->getPlayerStrategy()->getPlayerType() != "Cheater" && v[i]->getPlayerStrategy()->getPlayerType() != "Neutral")
            {
                Deploy *d = new Deploy();
                v[i]->issueOrder(d);
                continue;
            }

            // the player is allowed to advance order a maximum of 3 times, else move to the next
            else if (countAdvanceTerritories[i] != 3 && round != 1 && v[i]->getPlayerStrategy()->getPlayerType() != "Cheater" && v[i]->getPlayerStrategy()->getPlayerType() != "Neutral")
            {
                Advance *a = new Advance();
                v[i]->issueOrder(a);
                countAdvanceTerritories[i]++;
                continue;
            }

            // // if it arrives at the end of the player's cardsInHand array, skip this statement
            else if (v[i]->getHand()->cardsInHand.size() != 0 && indexHandVector[i] != v[i]->getHand()->cardsInHand.size() && round != 1 && v[i]->getPlayerStrategy()->getPlayerType() != "Cheater" && v[i]->getPlayerStrategy()->getPlayerType() != "Neutral")
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
                // remove the card from the hand if the order is issued !
                v[i]->getHand()->cardsInHand.erase(v[i]->getHand()->cardsInHand.begin() + indexHandVector[i]);
                indexHandVector[i]++;
                continue;
            }
            // when all of the previous possible orders are done, change the value to 1 for that player
            else if (outOfOrder[i] != 1)
            {
                cout << "\n"
                     << v[i]->getPlayerName() << " is out of orders !" << endl;
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
            cout << "\nNo more orders to issue for all players !\n"
                 << endl;
            moreOrder = false;
            break;
        }
    }
}

void GameEngine::executeOrdersPhase(vector<Player *> v)
{
    cout << "\n~~~~~~ISSUE EXECUTING PHASE~~~~~~\n"
         << endl;

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
            cout << "\nDone with all executions !" << endl;
            moreOrder = false;
        }
    }
}
void GameEngine::mainGameLoop(vector<Player *> v, Map *map)
{
    cout << "Starting the main game loop..." << endl;
    int round = 1;
    bool noWinner = true;
    do
    {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i]->getTerritories().size() == 0)
            {
                cout << v[i]->getPlayerName() << " has " << v[i]->getTerritories().size() << " territories !\nRemoving " << v[i]->getPlayerName() << " ..." << endl;
                v.erase(v.begin() + i);
            }
        }

        if (v.size() <= 1)
        {
            noWinner = false;
            cout << "One Player Left !\nEnd of game !\nCongratulations " << v[0]->getPlayerName() << " !!!!"
                 << endl;
            break;
        }

        cout << "\nRound " << round << endl;
        if (round != 1)
        {
            reinforcementPhase(v, map, round);
        }
        issueOrdersPhase(v, round);
        executeOrdersPhase(v);

        // added so that a player can draw a card in the next round
        for (Player *p : v)
        {
            p->roundReset();
        }
        resetNegotiatePairs();
        round++;

    } while (noWinner);
    // cout << "Game ending successfully. Returning from mainGameLoop." << endl;
    return;

    // string answer;
    // cout << "Winner !!! Player: " << v[0]->getPlayerName() << endl;
    // cout << "\nWould you like to play again ?\n<replay> if you want to replay !\n<quit> if you want to end the game..." << endl;
    // cin >> answer;

    // if (answer.compare("quit") == 0)
    // {
    //     cout << "Thanks for playing with us ! Goodbye !" << endl;
    //     return;
    // }

    // if (answer.compare("replay") == 0)
    // {
    // }
    // return;
}

// NOTES: first round of the game: ~DONE~
// reinforcement phase is skipped on the first round
// the advance and card orders are skipped on the first round

// list of what needs to be completed:
// My part only:
// - test reinforcementPhase() and add proper cout for testing ~DONE~
// - test issueOrderPhase() and add proper cout for testing ALSO the toDefend() and toAttack() ~DONE~

// - test issueExecution() and fix the orders issues
// - test out main game loop
// - create testMainGameLoop() in GameEngineDriver

// Other parts:
// - add shamma's command processor part to my part
// - make sure the orders have all the proper values
// - iloggable needs to work in my part
// - make sure that at startup, and at orders the territories are updated on the player owners
// - make sure that the orders keep track of the armies

// int main()
// {
//     MapLoader *ml = new MapLoader("MapTextFiles/South America.map");
//     Observer *o = new LogObserver();
//     // Player *p1 = new Player(o, "Ihana");
//     Player *p2 = new Player(o, "Shamma");
//     Player *p3 = new Player(o, "Tanya");
//     Player *p4 = new Player(o, "Naika");
//     Player *p5 = new Player(o, "MahJoup");
//     GameEngine *g = new GameEngine(o);

//     Benevolent *b = new Benevolent();
//     Cheater *c = new Cheater();
//     Aggressive *a = new Aggressive();
//     Neutral *n = new Neutral();
//     Human *h = new Human();

//     // b->setPlayer(p1);
//     c->setPlayer(p2);
//     a->setPlayer(p3);
//     n->setPlayer(p4);
//     h->setPlayer(p5);

//     // p1->setPlayerStrategy(b);
//     p2->setPlayerStrategy(c);
//     p3->setPlayerStrategy(a);
//     p4->setPlayerStrategy(n);
//     p5->setPlayerStrategy(h);

//     // cout << "\nplayer 1: " << p1->getPlayerName() << endl;
//     cout << "\nplayer 2: " << p2->getPlayerName() << endl;
//     cout << "\nplayer 3: " << p3->getPlayerName() << endl;
//     cout << "\nplayer 4: " << p4->getPlayerName() << endl;
//     cout << "\nPlayer 5: " << p5->getPlayerName() << endl;

//     vector<Player *> pList = getPlayerList();
//     // pList.push_back(p1);
//     pList.push_back(p2);
//     pList.push_back(p3);
//     pList.push_back(p4);
//     pList.push_back(p5);

//     // add a random loop to deisgnate territories to the players (this is usually done at startup)
//     for (Territory *t : ml->getMap()->getTerritories())
//     {
//         if (t->getContinent()->getName().compare("Central America") == 0)
//         {
//             p2->addTerritory(t);
//             t->setPlayer(p2);
//         }
//         else if (t->getContinent()->getName().compare("The Andes") == 0)
//         {
//             p5->addTerritory(t);
//             t->setPlayer(p5);
//         }
//         else if (t->getContinent()->getName().compare("The Highlands") == 0)
//         {
//             p3->addTerritory(t);
//             t->setPlayer(p3);
//         }
//         else
//         {
//             p4->addTerritory(t);
//             t->setPlayer(p4);
//         }
//     }

// cout << "\nreinforcement pool at the start of the game for " << p1->getPlayerName() << " is: " << p1->getReinforcementPool() << endl;
// cout << "\nreinforcement pool at the start of the game for " << p2->getPlayerName() << " is: " << p2->getReinforcementPool() << endl;

// cout << "\n----------Reinforcement Phase Test----------\n\n"
//      << endl;
// g->reinforcementPhase(pList, ml->getMap());
// cout << "\n"
//      << p1->getPlayerName() << " has " << p1->getReinforcementPool() << " many armies to deploy for this round !" << endl;
// cout << "\n"
//      << p2->getPlayerName() << " has " << p2->getReinforcementPool() << " many armies to deploy for this round !" << endl;

// cout << "\n----------Issue Ordering Phase Test----------"
//      << endl;

// add cards for each player (usually done in startup)
// Card *bomb = new Card(Card::BOMB);
// Card *blockade = new Card(Card::BLOCKADE);
// Card *airlift = new Card(Card::AIRLIFT);
// Card *negotiate = new Card(Card::NEGOTIATE);

// p1->addCard(bomb);
// p2->addCard(bomb);
// p1->addCard(blockade);
// p2->addCard(blockade);
// p1->addCard(airlift);
// p2->addCard(airlift);
// p1->addCard(negotiate);
// p2->addCard(negotiate);

// checks for the first round is only deploy
// cout << "\nFirst round ! " << endl;
// g->issueOrdersPhase(pList, 1);
// g->executeOrdersPhase(pList);

// // test for a bunch another round in the game with a bunch of random values of armies in the territories
// for (Territory *t : p1->getTerritories())
// {
//     t->setNumArmies(t->getName().length());
// }
// for (Territory *t : p2->getTerritories())
// {
//     t->setNumArmies(t->getName().length());
// }
// cout << "\nSecond round ! " << endl;
// g->reinforcementPhase(pList, ml->getMap());
// g->issueOrdersPhase(pList, 2);

// cout << "\n----------Issue Executing Phase Test----------"
//      << endl;
// g->executeOrdersPhase(pList);

// cout << "\n----------Main Game Loop Phase Test----------"
//      << endl;

// g->mainGameLoop(pList, ml->getMap());

// ~~~~~test for toDefend() and toAttack()

// cout << "Territories owned by " << p1->getPlayerName() << " before sorting based on priority are:\n"
//      << endl;

// for (Territory *t : p1->getTerritories())
// {
//     cout << t->getName() << endl;
//     t->setNumArmies(t->getName().length());
// }

// p1->toDefend();

// cout << "\nTerritories owned by " << p1->getPlayerName() << " after sorting based on priority are:\n"
//      << endl;

// for (Territory *t : p1->getTerritories())
// {
//     cout << t->getName() << endl;
// }

// cout << "\nEnemy territories of " << p1->getPlayerName() << " before sorting based on priority are:\n"
//      << endl;

// vector<Territory *> toAttackTest;
// vector<Territory *> p1Territories = p1->getTerritories();

// for (Territory *t : p1Territories)
// {
//     for (Territory *tadj : t->getAdjTerritories())
//     {

//         if (std::find(toAttackTest.begin(), toAttackTest.end(), tadj) == toAttackTest.end() && std::find(p1Territories.begin(), p1Territories.end(), tadj) == p1Territories.end())
//         {
//             toAttackTest.push_back(tadj);
//             tadj->setNumArmies(tadj->getName().length());
//         }
//     }
// }

// for (Territory *t : toAttackTest)
// {
//     cout << t->getName() << endl;
// }

// toAttackTest = p1->toAttack();

// cout << "\nEnemy territories of " << p1->getPlayerName() << " after sorting based on priority are:\n"
//      << endl;

// for (Territory *t : toAttackTest)
// {
//     cout << t->getName() << endl;
// }

// return 0;
// }
