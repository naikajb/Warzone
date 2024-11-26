#include "PlayerStrategies.h"

void testPlayerStrategies(){

    BenevolentPlayerStrategy* j = new BenevolentPlayerStrategy();
    CheaterPlayerStrategy* m = new CheaterPlayerStrategy();
    AggressivePlayerStrategy* t = new AggressivePlayerStrategy();
    NeutralPlayerStrategy* n = new NeutralPlayerStrategy();
    HumanPlayerStrategy* h = new HumanPlayerStrategy();

    Observer* obs = new LogObserver();

    j->setPlayer(new Player(obs,"J"));
    m->setPlayer(new Player(obs,"M"));
    t->setPlayer(new Player(obs,"T"));
    n->setPlayer(new Player(obs,"N"));
    h->setPlayer(new Player(obs,"H"));

    h->getPlayer()->setPlayerStrategy(h);

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

    t1->addAdjTerritories(t3);
    t3->addAdjTerritories(t1);
    t1->addAdjTerritories(t2);
    t2->addAdjTerritories(t1);

    t1->setPlayer(h->getPlayer());
    t2->setPlayer(h->getPlayer());

    t3->setPlayer(j->getPlayer());

    t4->setPlayer(n->getPlayer());



    
    h->getPlayer()->addTerritory(t1);
    
    h->getPlayer()->addTerritory(t2);

    j->getPlayer()->addTerritory(t3);

    n->getPlayer()->addTerritory(t4);

    h->getPlayer()->toDefend();

    Order* o = new Deploy();

    h->issueOrder(o);

    h->getPlayer()->getOrderList()->getOrders()[0]->execute();

    //Order* ne = new Advance();

    //t->issueOrder(ne);

    //t->getPlayer()->getOrderList()->getOrders()[0]->execute();

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


