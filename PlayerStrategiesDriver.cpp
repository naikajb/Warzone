#include "PlayerStrategies.h"

void testPlayerStrategies(){

    Benevolent* b = new Benevolent();
    Cheater* c = new Cheater();
    Aggressive* a = new Aggressive();
    Neutral* n = new Neutral();
    Human* h = new Human();

    Observer* obs = new LogObserver();

    b->setPlayer(new Player(obs,"B"));
    c->setPlayer(new Player(obs,"C"));
    a->setPlayer(new Player(obs,"A"));
    n->setPlayer(new Player(obs,"N"));
    h->setPlayer(new Player(obs,"H"));

    b->getPlayer()->setPlayerStrategy(b);
    c->getPlayer()->setPlayerStrategy(c);
    a->getPlayer()->setPlayerStrategy(a);
    n->getPlayer()->setPlayerStrategy(n);
    h->getPlayer()->setPlayerStrategy(h);
    
    Territory* t1 = new Territory("1",new Continent("C",1));
    Territory* t2 = new Territory("2",new Continent("C",1));
    Territory* t3 = new Territory("3",new Continent("C",1));
    Territory* t4 = new Territory("4",new Continent("C",1));
    Territory* t5 = new Territory("5",new Continent("C",1));
    Territory* t6 = new Territory("6",new Continent("C",1));

    t1->setNumArmies(90);
    t2->setNumArmies(40);
    t3->setNumArmies(30);
    t4->setNumArmies(31);
    t5->setNumArmies(20);
    t6->setNumArmies(21);

    addToPlayerList(b->getPlayer());
    addToPlayerList(c->getPlayer());
    addToPlayerList(a->getPlayer());
    addToPlayerList(n->getPlayer());
    addToPlayerList(h->getPlayer());

    t1->addAdjTerritories(t2);
    t2->addAdjTerritories(t1);

    t1->addAdjTerritories(t3);
    t3->addAdjTerritories(t1);

    t2->addAdjTerritories(t4);
    t4->addAdjTerritories(t2);

    t3->addAdjTerritories(t4);
    t4->addAdjTerritories(t3);

    t3->addAdjTerritories(t5);
    t5->addAdjTerritories(t3);

    t4->addAdjTerritories(t6);
    t6->addAdjTerritories(t6);

    t5->addAdjTerritories(t6);
    t6->addAdjTerritories(t5);

    //

    t1->setPlayer(h->getPlayer());
    h->getPlayer()->addTerritory(t1);

    t2->setPlayer(h->getPlayer());
    h->getPlayer()->addTerritory(t2);

    t3->setPlayer(n->getPlayer());
    n->getPlayer()->addTerritory(t3);

    t4->setPlayer(c->getPlayer());
    c->getPlayer()->addTerritory(t4);
    
    t5->setPlayer(a->getPlayer());
    a->getPlayer()->addTerritory(t5);

    t6->setPlayer(b->getPlayer());
    b->getPlayer()->addTerritory(t6);

    //

    Order* o = new Advance();

    a->issueOrder(o);
    c->issueOrder(o);

    for(Order* x : a->getPlayer()->getOrderList()->getOrders()){

        x->execute();

    }

    c->getPlayer()->getOrderList()->getOrders()[0]->execute();

    c->getPlayer()->getOrderList()->getOrders()[0]->execute();

    c->getPlayer()->roundReset();

    c->getPlayer()->getOrderList()->getOrders()[0]->execute();

} 

int mai(){

    testPlayerStrategies();

    return 0;
}


