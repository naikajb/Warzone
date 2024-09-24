#include "Map.h" // import Map.h header file

class Continent; // class Continent call for the Territory class

// defines the Territory constructor with an initilizer list
Territory::Territory(string name, Continent *continent) : name(name),
                                                          continent(continent)
{
}
// defines the Territory copy constructor with an initilizer list
Territory::Territory(const Territory &t)
{
    name = t.name;
    numArmies = t.numArmies;
    continent = t.continent;
    adjTerritories = t.adjTerritories;
}

Territory &Territory::operator=(Territory &o)
{

    this->name = o.name;
    this->numArmies = o.numArmies;
    this->continent = o.continent;
    this->adjTerritories = o.adjTerritories;

    return *this;
}

ostream &operator<<(ostream &out, Territory &o)
{

    string adjString = "(";

    for (Territory *t : o.getAdjTerritories())
    {

        adjString += (t->getName() + ",");
    }

    adjString += ")";

    out << "Name: " << o.getName() << ", Number of Armies: " << o.getNumArmies() << ", Continent: " << o.getContinent() << ", Adjacent Territories: " + adjString << std::endl;
    return out;
}

string Territory::getName() { return name; }                                  // getName() definition
int Territory::getNumArmies() { return numArmies; }                           // getNumArmies() definition
Continent *Territory::getContinent() { return continent; }                    // getContinent() definition
vector<Territory *> Territory::getAdjTerritories() { return adjTerritories; } // getAdjTerritories() definition

void Territory::setNumArmies(int numArmies) { numArmies = numArmies; } // setNumArmies() definition
// void Territory::setContinent(string continent){ continent = continent; }
void Territory::addAdjTerritories(Territory *adjTerritory) { adjTerritories.push_back(adjTerritory); } // addAdjTerritories() definition

// defines the Continent constructor with an initilizer list
Continent::Continent(string name, int bonus) : name(name),
                                               bonus(bonus)
{
}
// defines the Continent copy constructor with an initilizer list
Continent::Continent(const Continent &c)
{
    name = c.name;
    bonus = c.bonus;
    territories = c.territories;
}

Continent &Continent::operator=(Continent &o)
{

    this->name = o.name;
    this->bonus = o.bonus;
    this->territories = o.territories;

    return *this;
}

ostream &operator<<(ostream &out, Continent &o)
{

    string terrString = "(";

    for (Territory *t : o.getTerritories())
    {

        terrString += (t->getName() + ",");
    }

    terrString += ")";

    out << "Name: " << o.getName() << ", Bonus: " << o.getBonus() << ", Territories: " + terrString << std::endl;
    return out;
}

string Continent::getName() { return name; }                            // getName() definition
int Continent::getBonus() { return bonus; }                             // getBonus() definition
vector<Territory *> Continent::getTerritories() { return territories; } // getTerritories definition

void Continent::addTerritory(Territory *t) { territories.push_back(t); } // addTerritory definition

// defines the Map constructor with an initilizer list
Map::Map(string fileName) : fileName(fileName)
{
}
// defines the Map copy constructor with an initilizer list
Map::Map(const Map &m)
{

    fileName = m.fileName;
    territories = m.territories;
    continents = m.continents;
}

Map &Map::operator=(Map &o)
{

    this->fileName = o.fileName;
    this->territories = o.territories;
    this->continents = o.continents;

    return *this;
}

ostream &operator<<(ostream &out, Map &o)
{

    out << "Name: " << o.getFileName() << std::endl;
    return out;
}

string Map::getFileName() { return fileName; }
vector<Territory *> Map::getTerritories() { return territories; }
vector<Continent *> Map::getContinents() { return continents; }

void Map::addTerritory(Territory *t)
{ // addTerritory definition
    territories.push_back(t);
}

void Map::addContinent(Continent *c)
{ // addContinent definition
    continents.push_back(c);
}

MapLoader::MapLoader(string fileName) : fileName(fileName),
                                        map(loadMap(fileName))
{
}

MapLoader::MapLoader(MapLoader &ml)
{
    map = ml.map;
    fileName = ml.fileName;
}

MapLoader &MapLoader::operator=(MapLoader &o)
{

    this->map = o.map;
    this->fileName = o.fileName;

    return *this;
}

ostream &operator<<(ostream &out, MapLoader &o)
{

    out << "Name: " << o.getFileName() << std::endl;
    return out;
}

string MapLoader::getFileName() { return fileName; }

Map *MapLoader::getMap() { return map; }

Map *MapLoader::loadMap(string fileName)
{

    bool firstRead = true;

    Map *map = new Map(fileName);

    for (int i = 0; i < 2; i++)
    {

        std::ifstream file(fileName);

        string line;

        int state = 0;

        int lineNum = 0;

        while (getline(file, line))
        {

            if (line.length() > 1)
            {

                line.erase(line.size() - 1);
            }

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

                if (line.length() == 1)
                {
                    continue;
                }

                vector<string> v = splitString(line, '=');

                Continent *c = new Continent(v[0], std::stoi(v[1]));

                map->addContinent(c);
            }

            if (state == 2 && firstRead)
            {

                vector<string> v = splitString(line, ',');

                for (Continent *c : map->getContinents())
                {

                    if (c->getName().compare(v[3]) == 0)
                    {
                        Territory *t = new Territory(v[0], c);
                        map->addTerritory(t);
                        c->addTerritory(t);
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

vector<string> MapLoader::splitString(string line, char splitter)
{

    string x;
    std::stringstream ss(line);
    vector<string> returnedVector;

    while (getline(ss, x, splitter))
    {

        returnedVector.push_back(x);
    }
    return returnedVector;
}

void validate()
{ // validate() definition
}