#include "MapLoader.h"
#include <iostream> // import library that provides objects which can read user input and output data to the console or to a file
using std::cout;
using std::endl;

vector<string> splitString(string line, char splitter)
{ // splitString free function definition where splitter is the char delimiter

    string x;
    std::stringstream ss(line); // using the stringstream class for parsing
    vector<string> returnedVector;

    while (getline(ss, x, splitter))
    {

        returnedVector.push_back(x); // adds each string from the line in a vector
    }
    return returnedVector;
}
// createMap() definition
Map *createMap(string fileName)
{
    // std::cout << fileName << std::endl; // debug

    bool firstRead = true;

    Map *map = new Map(fileName);

    for (int i = 0; i < 2; i++)
    {

        ifstream file(fileName);

        string line;

        int state = 0;

        int lineNum = 0;

        while (getline(file, line))
        {

            // std::cout<<state<<std::endl; debug
            // std::cout<<firstRead<<std::endl; debug

            // if (line.length() > 1) // this caused issues so that it would stop after the first continent
            // {

            //     line.erase(line.size() - 1);
            // }

            if (line[0] == '[' && line[1] == 'C')
            {
                state = 1;
                continue;
            }

            if (line[0] == '[' && line[1] == 'T')
            {
                state = 2;
                continue;
            }

            if (state == 1 && firstRead)
            {

                if (line.length() == 0) // changed it from 1 to 0 because it was not reading after finishing Continents
                {
                    continue;
                }

                vector<string> v = splitString(line, '=');

                Continent *c = new Continent(v[0], std::stoi(v[1]));

                map->addContinent(c);

                // for (Continent* cc:map->getContinents()){
                // std::cout << cc->getName() <<  std::endl;
                // std::cout << cc->getBonus() <<  std::endl;
                // } debug
            }

            if (state == 2 && firstRead)
            {
                if (line.length() == 0)
                {
                    continue;
                }

                vector<string> v = splitString(line, ',');

                for (Continent *c : map->getContinents())
                {

                    if (c->getName().compare(v[3]) == 0)
                    {
                        Territory *t = new Territory(v[0], c);

                        map->addTerritory(t);
                        c->addTerritory(t);

                        // for (Territory *tt : map->getTerritories())
                        // {
                        //     std::cout << tt->getName() << std::endl;}
                        // } debug

                        // std::cout<< c->getTerritories()[0]->getName() <<std::endl; debug
                    }
                }
            }
            else if (state == 2)
            {
                if (line.length() == 0) // added this code
                {
                    continue;
                }
                vector<string> v = splitString(line, ',');

                for (int j = 0; j < v.size() - 4; j++)
                {

                    for (Territory *t : map->getTerritories())
                    {

                        if (v[j + 4].compare(t->getName()) == 0)
                        {

                            map->getTerritories()[lineNum]->addAdjTerritories(t);
                            break;
                        }
                    }
                }
                lineNum += 1;
            }
        }
        firstRead = false;
        file.clear();
    }
    // added code
    if (map->getContinents().size() > 32)
    {
        cout << "Unacceptable map ! It has " << map->getContinents().size() << " continents which is bigger than 32. Try Another map!" << endl;
        return NULL;
    }

    if (map->getTerritories().size() > 255)
    {
        cout << "Unacceptable map ! It has " << map->getTerritories().size() << " territories which is bigger than 255. Try Another map!" << endl;
        return NULL;
    }

    for (Territory *tt : map->getTerritories())
    {
        bool acceptable = true;
        for (Territory *ii : tt->getAdjTerritories())
        {
            if (ii->getAdjTerritories().size() > 10)
                cout << "Unacceptable map ! It has " << ii->getAdjTerritories().size() << " adjacent territories to " << ii->getName() << " which is bigger than 10. Try Another map!" << endl;
            acceptable = false;
            break;
        }
        if (acceptable == false)
        {
            break;
            return NULL;
        }
    }
    return map;
}

void DFSHelper(Territory *current, vector<Territory *> &visited)
{

    // std::cout << current->getName() << std::endl; // displaying all territories thru DFS

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

Map *testLoadMaps() // changed the return statement to map pointer
{
    // Map *map = createMap("MapTextFiles/UK.map");
    // Map *map = createMap("MapTextFiles/South America.map");
    Map *map = createMap("MapTextFiles/USA.map");
    // Map* map = createMap("Annys World.txt");

    if (DFS(map))
    {

        std::cout << "The map is a connected Graph (Verification 1)." << std::endl;
    }
    else
    {

        std::cout << "The map is NOT a connected Graph (Verification 1)." << std::endl;
    }

    return map;
}

int main()
{

    Map *map = testLoadMaps();

    cout << "Number of Continents: " << map->getContinents().size() << endl;
    cout << "Number of Territories: " << map->getTerritories().size() << endl;
    cout << "\n"
         << endl;

    for (Territory *tt : map->getTerritories())
    {
        for (Territory *ii : tt->getAdjTerritories())
        {
            cout << "Number of Adjacent Territories to " << ii->getName() << " : " << ii->getAdjTerritories().size() << endl;
        }
    }

    // std::cout << "\nthese are the continents" << std::endl;
    for (Continent *i : map->getContinents())
    {
        std::cout << "\nCountry: " << i->getName() << std::endl;

        std::cout << "\nthese are the territories of the continent: " << i->getName() << std::endl;

        for (Territory *t : i->getTerritories())
        {
            std::cout << t->getName() << std::endl;
        }
    }
    std::cout << "\nthese are the territories: " << std::endl;

    for (Territory *i : map->getTerritories())
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

// g++ -std=c++11 MapLoader.cpp Map.cpp

// THINGS TO BE ADDED:

// - comments for MapLoader.cpp and MapLoader.h
// - add the validate() method to the map.cpp and map.h (in the assign 1 pdf)