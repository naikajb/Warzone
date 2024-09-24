#include "MapLoader.h"

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
    std::cout << fileName << std::endl; // debug

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
            if (firstRead == false){
            std::cout<<line<<std::endl;
            std::cout<<"found"<<std::endl;
            }
            // std::cout<<state<<std::endl;
            // std::cout<<firstRead<<std::endl;

            // if (line.length() > 1)
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
                    std::cout<<"skip"<<std::endl;
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

Map *testLoadMaps()
{

    Map *map = createMap("USA.txt");
    // Map* map = createMap("Annys World.txt");
    std::cout << "hiiii";

    if (DFS(map))
    {

        std::cout << "The map is a connected Graph (Verification 1)." << std::endl;
    }
    else
    {

        std::cout << "The map is NOT a connected Graph (Verification 1)." << std::endl;
    }

    std::cout << "hi3";

    return map;
}

int main()
{
    std::cout << "Hello" << std::endl;

    Map *map = testLoadMaps();
    for (Continent *i : map->getContinents())
    {
        std::cout << i->getName() << std::endl;
    }
    std::cout << "" << std::endl;

    for (Territory *i : map->getTerritories())
    {
        std::cout << i->getName() << std::endl;
    }

    return 0;
}

// g++ -std=c++11 MapLoader.cpp Map.cpp