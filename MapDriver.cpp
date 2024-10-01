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

    cout << "Number of Continents: " << ml->getMap()->getContinents().size() << endl;
    cout << "Number of Territories: " << ml->getMap()->getTerritories().size() << endl;
    cout << "\n"
         << endl;

    for (Territory *tt : ml->getMap()->getTerritories())
    {
        for (Territory *ii : tt->getAdjTerritories())
        {
            cout << "Number of Adjacent Territories to " << ii->getName() << " : " << ii->getAdjTerritories().size() << endl;
        }
    }

    std::cout << "\nthese are the continents:" << std::endl;
    for (Continent *i : ml->getMap()->getContinents())
    {
        std::cout << "\nContinent: " << i->getName() << std::endl;

        std::cout << "\nthese are the territories of the continent: " << i->getName() << std::endl;

        for (Territory *t : i->getTerritories())
        {
            std::cout << t->getName() << std::endl;
        }
    }
    std::cout << "\nthese are the territories: " << std::endl;

    for (Territory *i : ml->getMap()->getTerritories())
    {
        std::cout << "\nTerritory: " << i->getName() << std::endl;

        cout << "\nthese are the adjacent territories to the territory: " << i->getName() << endl;

        for (Territory *ii : i->getAdjTerritories())
        {
            std::cout << ii->getName() << std::endl;
        }
    }
    delete ml;
    ml = NULL;
    return 0;
}

// g++ -std=c++11 MapDriver.cpp Map.cpp
// ./a.exe