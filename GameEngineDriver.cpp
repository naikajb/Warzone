// #include "GameEngine.h"
// #include <iostream>

// // free function, it controls the command loop that interacts with the GameEngine through the CommandParser
// /*void testGameStates() { // to accept command-line command, argc is the number of arguments, argv is the array of arguments

//     Observer* obs = new LogObserver();
//     std::string inputMode;
//     bool useConsole = false;
//     std::cout << "Welcome to the Game Engine!\n\n" << "Choose a mode to input commands: \n" << "1. Console\n" << "2. File\n" << "\nEnter 1 or 2:\n" << "> ";
//     std::cin >> inputMode;

//      // Select the appropriate CommandProcessor based on command-line argument
//     CommandProcessor* commandProcessor = nullptr;
//     FileLineReader* fileLineReader = nullptr;

//     if (inputMode == "1") {
//         commandProcessor = new CommandProcessor(obs);
//         //commandProcessor->Attach(obs);
//         useConsole = true;
//     }
//     else if (inputMode == "2") {
//         std::string fileName;
//         while (true) {
//             std::cout << "\nEnter the file name: ";
//             std::cin >> fileName;
//             try {
//                 fileLineReader = new FileLineReader(fileName);
//                 commandProcessor = new FileCommandProcessorAdapter(obs,fileLineReader);
//                 //commandProcessor->Attach(obs);
//                 break;
//             } catch (std::invalid_argument& e) {
//                 std::cerr << e.what() << std::endl;
//             }
//         }
//     }
//     else {
//         std::cerr << "\nInvalid input mode. Exiting..." << std::endl;
//         return;
//     }

//     GameEngine engine =  GameEngine(obs);
//     std::cout << "\nStarting Game Engine\n\n";

//     std::string input;
//     std::string unknown = "";

//     while (true) {
//         if(useConsole) {
//             std::cout << "Type a command " << std::endl;
//             std::cout << "> ";
//             std::getline(std::cin >> std::ws, input);
//             bool temp1 = engine.processConsoleCommand(input, commandProcessor);
//             if (input == "exit") {
//                 break;
//             }
//         }
//         else {
//             bool temp2 = engine.processFileCommand(unknown, commandProcessor);
//         }


//         // Command* cmd = commandProcessor->getCommand(input);
//         // if (!cmd) {
//         //     break;
//         // }

//     //     std::cout << "> ";
//     //     std::getline(std::cin >> std::ws, input);

//     //     if (input == "exit") {
//     //         break;
//     //     }
//     //     parser.parseCommand(input);
//  }
// };*/

// void testStartupPhase()
// {
//     Observer *o = new LogObserver();
//     GameEngine gm = GameEngine(o);
//     gm.startupPhase();
// }

// // void testMainGameLoop(){
// int main()
// {

//     MapLoader *ml = new MapLoader("MapTextFiles/South America.map");
//     Observer *o = new LogObserver();
//     Player *p1 = new Player(o, "Ihana");
//     Player *p2 = new Player(o, "Shamma");
//     GameEngine *g = new GameEngine(o);
//     Player *neutral = new Player(o, "Neutral");

//     cout << "\nplayer 1: " << p1->getPlayerName() << endl;
//     cout << "\nplayer 2: " << p2->getPlayerName() << endl;

//     addToPlayerList(p1);
//     addToPlayerList(p2);
//     addToPlayerList(neutral);
//     vector<Player *> pList = getPlayerList();
//     // pList.push_back(p1);
//     // pList.push_back(p2);

//     // add a random loop to deisgnate territories to the players (this is usually done at startup)
//     for (Territory *t : ml->getMap()->getTerritories())
//     {
//         if (t->getContinent()->getName().compare("Central America") == 0 || t->getContinent()->getName().compare("The Highlands") == 0)
//         {
//             p1->addTerritory(t);
//             t->setPlayer(p1);
//             // cout << "\n"
//             //      << t->getName() << " was added for " << p1->getPlayerName() << endl;
//         }
//         else
//         {
//             p2->addTerritory(t);
//             t->setPlayer(p2); // this is to test territories with no players for issueOrderPhase()

//             // cout << "\n"
//             //      << t->getName() << " was added for " << p2->getPlayerName() << endl;
//         }
//     }

//     // cout << "\nreinforcement pool at the start of the game for " << p1->getPlayerName() << " is: " << p1->getReinforcementPool() << endl;
//     // cout << "\nreinforcement pool at the start of the game for " << p2->getPlayerName() << " is: " << p2->getReinforcementPool() << endl;

//     // cout << "\n----------Reinforcement Phase Test----------\n\n"
//     //      << endl;
//     // g->reinforcementPhase(pList, ml->getMap());
//     // cout << "\n"
//     //      << p1->getPlayerName() << " has " << p1->getReinforcementPool() << " many armies to deploy for this round !" << endl;
//     // cout << "\n"
//     //      << p2->getPlayerName() << " has " << p2->getReinforcementPool() << " many armies to deploy for this round !" << endl;

//     // cout << "\n----------Issue Ordering Phase Test----------"
//     //      << endl;

//     // add cards for each player (usually done in startup)
//     Card *bomb = new Card(Card::BOMB);
//     Card *blockade = new Card(Card::BLOCKADE);
//     Card *airlift = new Card(Card::AIRLIFT);
//     Card *negotiate = new Card(Card::NEGOTIATE);

//     p1->addCard(bomb);
//     p2->addCard(bomb);
//     p1->addCard(blockade);
//     p2->addCard(blockade);
//     p1->addCard(airlift);
//     p2->addCard(airlift);
//     p1->addCard(negotiate);
//     p2->addCard(negotiate);

//     // checks for the first round is only deploy
//     // cout << "\nFirst round ! " << endl;
//     // g->issueOrdersPhase(pList, 1);
//     // g->executeOrdersPhase(pList);

//     // // test for a bunch another round in the game with a bunch of random values of armies in the territories
//     // for (Territory *t : p1->getTerritories())
//     // {
//     //     t->setNumArmies(t->getName().length());
//     // }
//     // for (Territory *t : p2->getTerritories())
//     // {
//     //     t->setNumArmies(t->getName().length());
//     // }
//     // cout << "\nSecond round ! " << endl;
//     // g->reinforcementPhase(pList, ml->getMap());
//     // g->issueOrdersPhase(pList, 2);

//     // cout << "\n----------Issue Executing Phase Test----------"
//     //      << endl;
//     // g->executeOrdersPhase(pList);

//     cout << "\n----------Main Game Loop Phase Test----------"
//          << endl;

//     g->mainGameLoop(pList, ml->getMap());

//     // Clean up dynamically allocated memory

//     // // Delete Players
//     // delete p1;
//     // p1 = nullptr;

//     // delete p2;
//     // p2 = nullptr;

//     // delete neutral;
//     // neutral = nullptr;

//     // // Delete GameEngine
//     // delete g;
//     // g = nullptr;

//     // // Delete MapLoader
//     // delete ml;
//     // ml = nullptr;

//     // // Delete Cards
//     // delete bomb;
//     // bomb = nullptr;

//     // delete blockade;
//     // blockade = nullptr;

//     // delete airlift;
//     // airlift = nullptr;

//     // delete negotiate;
//     // negotiate = nullptr;

//     // // Clear the player list vector and delete each player pointer if they were dynamically allocated
//     // for (Player* player : pList) {
//     //     delete player;
//     // }
//     // pList.clear(); // Clear the vector to avoid dangling pointers

//     // // Delete the observer if no other object depends on it
//     // delete o;
//     // o = nullptr;

//     // ~~~~~test for toDefend() and toAttack()

//     // cout << "Territories owned by " << p1->getPlayerName() << " before sorting based on priority are:\n"
//     //      << endl;

//     // for (Territory *t : p1->getTerritories())
//     // {
//     //     cout << t->getName() << endl;
//     //     t->setNumArmies(t->getName().length());
//     // }

//     // p1->toDefend();

//     // cout << "\nTerritories owned by " << p1->getPlayerName() << " after sorting based on priority are:\n"
//     //      << endl;

//     // for (Territory *t : p1->getTerritories())
//     // {
//     //     cout << t->getName() << endl;
//     // }

//     // cout << "\nEnemy territories of " << p1->getPlayerName() << " before sorting based on priority are:\n"
//     //      << endl;

//     // vector<Territory *> toAttackTest;
//     // vector<Territory *> p1Territories = p1->getTerritories();

//     // for (Territory *t : p1Territories)
//     // {
//     //     for (Territory *tadj : t->getAdjTerritories())
//     //     {

//     //         if (std::find(toAttackTest.begin(), toAttackTest.end(), tadj) == toAttackTest.end() && std::find(p1Territories.begin(), p1Territories.end(), tadj) == p1Territories.end())
//     //         {
//     //             toAttackTest.push_back(tadj);
//     //             tadj->setNumArmies(tadj->getName().length());
//     //         }
//     //     }
//     // }

//     // for (Territory *t : toAttackTest)
//     // {
//     //     cout << t->getName() << endl;
//     // }

//     // toAttackTest = p1->toAttack();

//     // cout << "\nEnemy territories of " << p1->getPlayerName() << " after sorting based on priority are:\n"
//     //      << endl;

//     // for (Territory *t : toAttackTest)
//     // {
//     //     cout << t->getName() << endl;
//     // }
// }

// // int main() {

// //     //testGameStates();
// //     testStartupPhase();

// //     return 0;
// // }