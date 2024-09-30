#include "MapDriver.h"
#include <iostream>
using std::cout;
using std::endl;

void testLoadMaps(MapLoader* ml)
{

    // MapLoader *ml = new MapLoader("MapTextFiles\\South America.map");

    if (DFS(ml->getMap()))
    {

        std::cout << "Map is a connected Graph (V1)." << std::endl;
    }
    else
    {

        std::cout << "Map is a NOT connected Graph (V1)." << std::endl;
    }

    bool v2 = true;

    for (Continent *c : ml->getMap()->getContinents())
    {

        if (!DFSC(c))
        {
            v2 = false;
            break;
        }
    }

    if (v2)
    {

        std::cout << "Continents are connected subgraphs (V2)." << std::endl;
    }
    else
    {

        std::cout << "NOT all Continents are connected subgraphs (V2)." << std::endl;
    }

    if (uniqueCountry(ml->getMap()))
    {

        std::cout << "Territories belong to one and only one Continent (V3)." << std::endl;
    }
    else
    {

        std::cout << "At least one Territory belongs to more than one Continent (V3)." << std::endl;
    }
}

void DFSHelper(Territory *current, vector<Territory *> &visited)
{

    for (Territory *t : current->getAdjTerritories())
    {
        bool contained = false;

        for (Territory *t2 : visited)
        {
            if (t->getName().compare(t2->getName()) == 0)
            {
                contained = true;
                break;
            }
        }

        if (!contained)
        {
            visited.push_back(t);
            DFSHelper(t, visited);
        }
    }
}

bool DFS(Map *map)
{
    vector<Territory *> visited;
    visited.push_back(map->getTerritories()[0]);
    DFSHelper(map->getTerritories()[0], visited);
    return (visited.size() == map->getTerritories().size());
}

void DFSContinent(Territory *current, vector<Territory *> &visited)
{

    for (Territory *t : current->getAdjTerritories())
    {

        if (t->getContinent()->getName().compare(current->getContinent()->getName()) != 0)
        {
            continue;
        }

        bool contained = false;

        for (Territory *t2 : visited)
        {
            if (t->getName().compare(t2->getName()) == 0)
            {
                contained = true;
                break;
            }
        }

        if (!contained)
        {
            visited.push_back(t);
            DFSContinent(t, visited);
        }
    }
}

bool DFSC(Continent *c)
{

    vector<Territory *> visited;
    visited.push_back(c->getTerritories()[0]);
    DFSContinent(c->getTerritories()[0], visited);
    return (visited.size() == c->getTerritories().size());
}

bool uniqueCountry(Map *map)
{

    for (Territory *t : map->getTerritories())
    {

        int count(0);

        for (Continent *c : map->getContinents())
        {

            for (Territory *t2 : c->getTerritories())
            {

                if (t->getName().compare(t2->getName()) == 0)
                {
                    count += 1;
                }
            }
        }

        if (count > 1)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    
    MapLoader ml("MapTextFiles\\South America.map");
    // MapLoader *pml = &ml;
    // Map *map = pml->loadMap(pml->getFileName());

    cout << "Number of Continents: " << ml.getMap()->getContinents().size() << endl;
    cout << "Number of Territories: " <<ml.getMap()->getTerritories().size() << endl;
    cout << "\n"
         << endl;

    for (Territory *tt : ml.getMap()->getTerritories())
    {
        for (Territory *ii : tt->getAdjTerritories())
        {
            cout << "Number of Adjacent Territories to " << ii->getName() << " : " << ii->getAdjTerritories().size() << endl;
        }
    }

    std::cout << "\nthese are the continents:" << std::endl;
    for (Continent *i : ml.getMap()->getContinents())
    {
        std::cout << "\nContinent: " << i->getName() << std::endl;

        std::cout << "\nthese are the territories of the continent: " << i->getName() << std::endl;

        for (Territory *t : i->getTerritories())
        {
            std::cout << t->getName() << std::endl;
        }
    }
    std::cout << "\nthese are the territories: " << std::endl;

    for (Territory *i : ml.getMap()->getTerritories())
    {
        std::cout << "\nTerritory: " << i->getName() << std::endl;

        cout << "\nthese are the adjacent territories to the territory: " << i->getName() << endl;

        for (Territory *ii : i->getAdjTerritories())
        {
            std::cout << ii->getName() << std::endl;
        }
    }

    return 0;
}

// g++ -std=c++11 MapDriver.cpp Map.cpp
// ./a.exe