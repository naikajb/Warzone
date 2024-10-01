#include "MapDriver.h"
#include <iostream>
using std::cout;
using std::endl;

vector<Map *> testLoadMaps(vector<Map *> mapSet)
{
    vector<Map *> validMaps;
    bool valid = true;

    for (Map *m : mapSet)
    {
        valid = Map::validate(m);

        if (valid == true)
            validMaps.push_back(m);
    }

    return validMaps;
}

int main()
{

    MapLoader *ml = new MapLoader("MapTextFiles\\South America.map");
    
    // debug of the testLoadMaps()
    // MapLoader *ml1 = new MapLoader("MapTextFiles\\USA.map");
    // MapLoader *ml2 = new MapLoader("MapTextFiles\\Asia 1200.map"); // invalid map test

    // vector<Map *> allMapList;
    // vector<Map *> validMapList;

    // allMapList.push_back(ml->getMap());
    // allMapList.push_back(ml1->getMap());
    // allMapList.push_back(ml2->getMap());

    // validMapList = testLoadMaps(allMapList);

    // cout << "all maps: \n";

    // for (Map *am : allMapList)
    // {
    //     cout << am->getFileName() << endl;
    // }
    // cout << "\nvalid maps: \n";
    // for (Map *vm : validMapList)
    // {
    //     cout << vm->getFileName() << endl;
    // }



    // debug to see if the validate() works
    // Map::validate(ml->getMap());

    // debug to see if the file is read properly
    // cout << "Number of Continents: " << ml->getMap()->getContinents().size() << endl;
    // cout << "Number of Territories: " << ml->getMap()->getTerritories().size() << endl;
    // cout << "\n"
    //      << endl;

    // for (Territory *tt : ml->getMap()->getTerritories())
    // {
    //     for (Territory *ii : tt->getAdjTerritories())
    //     {
    //         cout << "Number of Adjacent Territories to " << ii->getName() << " : " << ii->getAdjTerritories().size() << endl;
    //     }
    // }

    // std::cout << "\nthese are the continents:" << std::endl;
    // for (Continent *i : ml->getMap()->getContinents())
    // {
    //     std::cout << "\nContinent: " << i->getName() << std::endl;

    //     std::cout << "\nthese are the territories of the continent: " << i->getName() << std::endl;

    //     for (Territory *t : i->getTerritories())
    //     {
    //         std::cout << t->getName() << std::endl;
    //     }
    // }
    // std::cout << "\nthese are the territories: " << std::endl;

    // for (Territory *i : ml->getMap()->getTerritories())
    // {
    //     std::cout << "\nTerritory: " << i->getName() << std::endl;

    //     cout << "\nthese are the adjacent territories to the territory: " << i->getName() << endl;

    //     for (Territory *ii : i->getAdjTerritories())
    //     {
    //         std::cout << ii->getName() << std::endl;
    //     }
    // }

    
    
    //debug of the assignment operator and overloaded stream insertion
    // MapLoader *ml2;
    // ml2 = ml;

    // Territory *t = ml->getMap()->getTerritories()[0];
    // cout << *t;

    // Continent *c = ml->getMap()->getContinents()[0];
    // cout << *c;

    // cout << *(ml->getMap());

    // cout << "test for overloaded operator stream\n" << endl;

    // Territory *t2 = ml2->getMap()->getTerritories()[0];
    // cout << *t2;

    // Continent *c2 = ml2->getMap()->getContinents()[0];
    // cout << *c2;

    // cout << *(ml2->getMap());

    delete ml;
    ml = NULL;
    return 0;
}

// g++ -std=c++11 MapDriver.cpp Map.cpp
// ./a.exe