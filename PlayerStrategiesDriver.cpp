#include "PlayerStrategies.h"

void testPlayerStrategies(){

    BenevolentPlayerStrategy* j = new BenevolentPlayerStrategy();
    CheaterPlayerStrategy* m = new CheaterPlayerStrategy();
    AggressivePlayerStrategy* t = new AggressivePlayerStrategy();
    NeutralPlayerStrategy* n = new NeutralPlayerStrategy();

    Observer* obs = new LogObserver();

    j->setPlayer(new Player(obs,"J"));
    m->setPlayer(new Player(obs,"M"));
    t->setPlayer(new Player(obs,"T"));
    n->setPlayer(new Player(obs,"N"));


    Territory* t1 = new Territory("1",new Continent("C",1));
    Territory* t2 = new Territory("2",new Continent("C",1));
    Territory* t3 = new Territory("3",new Continent("C",1));
    Territory* t4 = new Territory("4",new Continent("C",1));

    t1->setNumArmies(90);
    t2->setNumArmies(40);
    t3->setNumArmies(30);
    t4->setNumArmies(31);

    addToPlayerList(j->getPlayer());
    addToPlayerList(m->getPlayer());
    addToPlayerList(t->getPlayer());
    addToPlayerList(n->getPlayer());
    
    j->getPlayer()->addTerritory(t1);
    
    m->getPlayer()->addTerritory(t2);

    t->getPlayer()->addTerritory(t3);

    n->getPlayer()->addTerritory(t4);

    Blockade* ne = new Blockade();

    j->issueOrder(ne);

    j->getPlayer()->getOrderList()->getOrders()[0]->execute();

    //cout << t1->getNumArmies() << endl;


    

    //nps->toDefend();

    //AggressivePlayerStrategy* aps = new AggressivePlayerStrategy();

    /*for(Player* p: getPlayerList()){

        cout << p->getPlayerName() << endl;

    }

    nps->becomeAggressive();

    for(Player* p: getPlayerList()){

        cout << p->getPlayerName() << endl;

    }*/


    //cout << "BON MATIN" << endl;



} 

int main(){

    testPlayerStrategies();

    return 0;
}


