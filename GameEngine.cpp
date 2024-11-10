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
GameEngine::GameEngine() : currentState(GameStateStrings[0]), commandProcessor(new CommandProcessor())
{

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
    Notify(this);
}

std::string GameEngine::stringToLog()
{
    return "GameEngine changed state to " + std::string(currentState);
}

// function to process commands entered by the user
void GameEngine::processCommand(std::string &command)
{

    Command *cmd = commandProcessor->getCommand(command);

    std::cout << "\nCurrent State: " << getCurrentState() << "\n"
              << std::endl;

    if ((commandProcessor->validate(cmd, this->getCurrentState())) == true)
    {
        stateTransition(cmd);
    }
    else
    {
        std::cout << "Invalid command. Try again.\n"
                  << std::endl;
    };
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

    bool moreOrder = true;
    while (moreOrder)
    {
        int countDone = 0;
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i]->getReinforcementTemp() != 0)
            {
                Deploy *d = new Deploy();
                v[i]->issueOrder(d);
                cout << "remaining armies for " << v[i]->getPlayerName() << " " << v[i]->getReinforcementTemp() << endl;
                continue;
            }

            // if it arrives at the end of the player's territory array, skip this if statement
            else if (countAdvanceTerritories[i] != 3)
            {
                Advance *a = new Advance();
                v[i]->issueOrder(a);

                countAdvanceTerritories[i]++;
                cout << "count for " << v[i]->getPlayerName() << " for advance " << countAdvanceTerritories[i]<< endl;
                continue;
            }
            // // if it arrives at the end of the player's cardsInHand array, skip this statement
            // else if (v[i]->getHand()->cardsInHand.size() != 0)
            // {
            //     if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Bomb"))
            //     {
            //         Bomb *b = new Bomb();
            //         v[i]->issueOrder(b);
            //     }

            //     if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Negotiate"))
            //     {
            //         Negotiate *n = new Negotiate();
            //         v[i]->issueOrder(n);
            //     }

            //     if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Blockade"))
            //     {
            //         Blockade *b = new Blockade();
            //         v[i]->issueOrder(b);
            //     }

            //     if (v[i]->getHand()->cardsInHand[indexHandVector[i]]->getCardType().compare("Airlift"))
            //     {
            //         Airlift *a = new Airlift();
            //         v[i]->issueOrder(a);
            //     }

            //     indexHandVector[i]++;
            //     continue;
            // }

            // when all of the previous possible orders are done, change the value to 1 for that player
            else if (outOfOrder[i] != 1)
            {
                cout<<"out of order" << endl;
                outOfOrder[i] = 1;
            }
        }

        // calculate the total number of players that are done
        for (int j : outOfOrder)
        {
            if (outOfOrder[j] == 1)
            {
                cout<<"check"<<endl;
                countDone++;
            }
        }

        // if all players are done, the loop is done !
        if (countDone == v.size())
        {
            cout<<"end"<<endl;
            moreOrder = false;
        }
    }
}

void GameEngine::executeOrdersPhase(vector<Player *> v)
{
}
void GameEngine::mainGameLoop(vector<Player *> v)
{
}

int main()
{

    MapLoader *ml = new MapLoader("MapTextFiles\\South America.map");
    Player *p1 = new Player("Ihana");
    Player *p2 = new Player("Shamma");
    vector<Player *> pList;

    pList.push_back(p1);
    pList.push_back(p2);

    for (Territory *t : ml->getMap()->getTerritories())
    {
        // randomly assign an original value of armies for debugging for each territory
        t->setNumArmies(t->getName().length());

        if (t->getContinent()->getName().compare("Central America") == 0 || t->getContinent()->getName().compare("The Highlands") == 0)
        {
            p1->addTerritory(t);
        }
        else
        {
            p2->addTerritory(t);
        }
    }

    cout << "player 1 territories: " << endl;

    for (Territory *t : p1->getTerritories())
    {
        t->setPlayer(p1);
        cout << "Player owner of " << t->getName() << " is " << t->getPlayer()->getPlayerName() << endl;
    }

    cout << "\nplayer 2 territories: " << endl;

    for (Territory *t : p2->getTerritories())
    {
        t->setPlayer(p2);
        cout << "Player owner of " << t->getName() << " is " << t->getPlayer()->getPlayerName() << endl;
    }

    cout << "\nplayer 1 reinforcement pool at the beginning of the game: " << p1->getReinforcementPool() << endl;
    cout << "\nplayer 2 reinforcement pool at the beginning of the game: " << p2->getReinforcementPool() << "\n"
         << endl;

    GameEngine g;
    g.reinforcementPhase(pList, ml->getMap());

    cout << "\nplayer 1 reinforcement pool after acquired territories: " << p1->getReinforcementPool() << endl;
    cout << "\nplayer 2 reinforcement pool after acquired territories: " << p2->getReinforcementPool() << "\n"
         << endl;

    // p1->toDefend();
    // p2->toDefend();
    // p1->toAttack();
    // p2->toAttack();

    p1->setReinforcementPool(50);
    p2->setReinforcementPool(50);

    g.issueOrdersPhase(pList);

    return 0;
}