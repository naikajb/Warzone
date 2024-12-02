#include "PlayerStrategies.h"
#include "GameEngine.h"

void testPlayerStrategies(){

    MapLoader *ml = new MapLoader("MapTextFiles/South America.map");
    Observer *o = new LogObserver();
    Player *p1 = new Player(o, "Ihana");
    Player *p2 = new Player(o, "Shamma");
    Player *p3 = new Player(o, "Tanya");
    Player *p4 = new Player(o, "Naika");
    Player *p5 = new Player(o, "MahJoup");
    GameEngine *g = new GameEngine(o);

    Benevolent *b = new Benevolent();
    Cheater *c = new Cheater();
    Aggressive *a = new Aggressive();
    Neutral *n = new Neutral();
    Human *h = new Human();

    b->setPlayer(p1);
    c->setPlayer(p2);
    a->setPlayer(p3);
    n->setPlayer(p4);
    // h->setPlayer(p5);

    p1->setPlayerStrategy(b);
    p2->setPlayerStrategy(c);
    p3->setPlayerStrategy(a);
    p4->setPlayerStrategy(n);
    // p5->setPlayerStrategy(h);

    cout << "\nplayer 1: " << p1->getPlayerName() << endl;
    cout << "\nplayer 2: " << p2->getPlayerName() << endl;
    cout << "\nplayer 3: " << p3->getPlayerName() << endl;
    cout << "\nplayer 4: " << p4->getPlayerName() << endl;
    // cout << "\nPlayer 5: " << p5->getPlayerName() << endl;

    vector<Player *> pList = getPlayerList();
    // pList.push_back(p1);
    pList.push_back(p2);
    pList.push_back(p3);
    pList.push_back(p4);
    pList.push_back(p1);

    // add a random loop to deisgnate territories to the players (this is usually done at startup)
    for (Territory *t : ml->getMap()->getTerritories())
    {
        if (t->getContinent()->getName().compare("Central America") == 0)
        {
            p2->addTerritory(t);
            t->setPlayer(p2);
        }
        else if (t->getContinent()->getName().compare("The Andes") == 0)
        {
            p1->addTerritory(t);
            t->setPlayer(p5);
        }
        else if (t->getContinent()->getName().compare("The Highlands") == 0)
        {
            p3->addTerritory(t);
            t->setPlayer(p3);
        }
        else
        {
            p4->addTerritory(t);
            t->setPlayer(p4);
        }
    }

// cout << "\nreinforcement pool at the start of the game for " << p1->getPlayerName() << " is: " << p1->getReinforcementPool() << endl;
// cout << "\nreinforcement pool at the start of the game for " << p2->getPlayerName() << " is: " << p2->getReinforcementPool() << endl;

// cout << "\n----------Reinforcement Phase Test----------\n\n"
//      << endl;
// g->reinforcementPhase(pList, ml->getMap(),1);
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

// // checks for the first round is only deploy
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

cout << "\n----------Main Game Loop Phase Test----------"
     << endl;

g->mainGameLoop(pList, ml->getMap(), 100);

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


} 

// int mai(){

//     testPlayerStrategies();

//     return 0;
// }


