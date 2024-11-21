#include "PlayerStrategies.h"

void testPlayerStrategies(){

    BenevolentPlayerStrategy* nps = new BenevolentPlayerStrategy();

    Observer* obs = new LogObserver();

    nps->setPlayer(new Player(obs,"Jacob"));

    Territory* t1 = new Territory("1",new Continent("C",1));
    Territory* t2 = new Territory("2",new Continent("C",1));
    Territory* t3 = new Territory("3",new Continent("C",1));
    Territory* t4 = new Territory("4",new Continent("C",1));

    t1->setNumArmies(90);
    t2->setNumArmies(40);
    t3->setNumArmies(30);
    t4->setNumArmies(31);



    nps->getPlayer()->addTerritory(t1);
    
    nps->getPlayer()->addTerritory(t2);

    nps->getPlayer()->addTerritory(t3);

    nps->getPlayer()->addTerritory(t4);

    nps->toDefend();


    //nps->becomeAggressive();


    cout << "BON MATIN" << endl;



} 

int main(){

    testPlayerStrategies();

    return 0;
}


