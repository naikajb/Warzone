#include "Map.h" // import Map.h header file

// TERRITORY CLASS

// defines the Territory constructor with an initilizer list
Territory::Territory(string name, Continent *continent) : name(name),
                                                          continent(continent), 
                                                          numArmies(0)
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

// Overloaded assignment operator for the Territory class definition
Territory &Territory::operator=(const Territory &o)
{
    this->name = o.name;
    this->numArmies = o.numArmies;
    this->continent = o.continent;
    this->adjTerritories = o.adjTerritories;

    return *this;
}
// Overloaded Stream insertion operator for the Territory class definition
// prints name of territory, the number of armies, the continent, and its adjacent territories
ostream &operator<<(ostream &out, Territory &o)
{

    string adjString;

    for (Territory *t : o.getAdjTerritories())
    {
        adjString += (t->getName() + "\n");
    }

    out << "-----------------------------------------------------------------\n"
        << "Territory Name: " << o.getName() << "\n\nNumber of Armies: " << o.getNumArmies() << "\n\nContinent: " << o.getContinent()->getName() << "\n\nAdjacent Territorie(s): \n" + adjString << "-----------------------------------------------------------------" << std::endl;
    return out;
}

string Territory::getName() { return name; }                                  // getName() definition
int Territory::getNumArmies() { return numArmies; }                           // getNumArmies() definition
Continent *Territory::getContinent() { return continent; }                    // getContinent() definition
vector<Territory *> Territory::getAdjTerritories() { return adjTerritories; } // getAdjTerritories() definition

void Territory::setNumArmies(int numArmies) { numArmies = numArmies; } // setNumArmies() definition
void Territory::addAdjTerritories(Territory *adjTerritory) { adjTerritories.push_back(adjTerritory); } // addAdjTerritories() definition

// CONTINENT CLASS

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
// Overloaded assignment operator for the Continent class definition
Continent &Continent::operator=(const Continent &o)
{

    this->name = o.name;
    this->bonus = o.bonus;
    this->territories = o.territories;

    return *this;
}
// Overloaded Stream insertion operator for the Continent class definition
// prints name of continent, the bonus, and its territories
ostream &operator<<(ostream &out, Continent &o)
{
    string terrString;

    for (Territory *t : o.getTerritories())
    {

        terrString += (t->getName() + "\n");
    }

    out << "-----------------------------------------------------------------\n"
        << "Continent Name: " << o.getName() << "\n\nBonus: " << o.getBonus() << "\n\nTerritory(ies): \n" + terrString << "-----------------------------------------------------------------" << std::endl;
    return out;
}

string Continent::getName() { return name; }                            // getName() definition
int Continent::getBonus() { return bonus; }                             // getBonus() definition
vector<Territory *> Continent::getTerritories() { return territories; } // getTerritories definition

void Continent::addTerritory(Territory *t) { territories.push_back(t); } // addTerritory definition

// MAP CLASS

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
// Overloaded assignment operator for the Map class definition
Map &Map::operator=(const Map &o)
{

    this->fileName = o.fileName;
    this->territories = o.territories;
    this->continents = o.continents;

    return *this;
}
// Overloaded Stream insertion operator for the Map class definition
// prints name of the file, the continents, the territories
ostream &operator<<(ostream &out, Map &o)
{
    string terrString;

    for (Territory *t : o.getTerritories())
    {

        terrString += (t->getName() + "\n");
    }

    string contString;

    for (Continent *c : o.getContinents())
    {
        contString += (c->getName() + "\n");
    }

    out << "-----------------------------------------------------------------\n"
        << "File Name: " << o.getFileName() << "\n\nContinent(s): \n"
        << contString << "\nTerritory(ies): \n"
        << terrString << "-----------------------------------------------------------------" << std::endl;
    return out;
}

string Map::getFileName() { return fileName; }                    // getFileName definition
vector<Territory *> Map::getTerritories() { return territories; } // getTerritories definition
vector<Continent *> Map::getContinents() { return continents; }   // getContinents definition

// addTerritory definition
void Map::addTerritory(Territory *t)
{
    territories.push_back(t);
}

// addContinent definition
void Map::addContinent(Continent *c)
{
    continents.push_back(c);
}

// static validate() definition
bool Map::validate(Map *m)
{
    cout << "-----------------------------------------------------------------\n"<< "Validation for the " << m->getFileName() << " in session...\n"
         << endl;

    // checks if the map is a connected graph, else invalid map return false
    if (DFS(m))
    {

        std::cout << "Map is a connected Graph (V1)." << std::endl;
    }
    else
    {

        std::cout << "Invalid map ! Map is a NOT connected Graph (V1).\n-----------------------------------------------------------------" << std::endl;
        return false;
    }

    bool v2 = true;

    for (Continent *c : m->getContinents())
    {

        if (!DFSC(c))
        {
            v2 = false;
            break;
        }
    }

    // checks if the continents are connected subgraphs, else invalid map return false
    if (v2)
    {

        std::cout << "Continents are connected subgraphs (V2)." << std::endl;
    }
    else
    {

        std::cout << "Invalid map ! NOT all Continents are connected subgraphs (V2).\n-----------------------------------------------------------------" << std::endl;
        return false;
    }

    // checks if the territories all belong to one and only one continent, else invalid map return false 
    if (uniqueCountry(m))
    {

        std::cout << "Territories belong to one and only one Continent (V3)." << std::endl;
    }
    else
    {

        std::cout << "Invalid map! At least one Territory belongs to more than one Continent (V3).\n-----------------------------------------------------------------" << std::endl;
        return false;
    }

    // if the map created has more than 32 countries, invalid map return false
    if (m->getContinents().size() > 32)
    {
        cout << "Invalid map ! It has " << m->getContinents().size() << " continents which is bigger than 32.\n-----------------------------------------------------------------" << endl;
        return false;
    }
    else{
        cout << "Map has " <<  m->getContinents().size() << " continents." << endl;
    }

    // if the map created has more than 255 territories, invalid map return false
    if (m->getTerritories().size() > 255)
    {
        cout << "Invalid map ! It has " << m->getTerritories().size() << " territories which is bigger than 255.\n-----------------------------------------------------------------" << endl;
        return false;
    }
    else{
        cout << "Map has " <<  m->getTerritories().size() << " territories." << endl;
    }

    // if the map has a territory with more than 10 adjacent territories, invalid map return false
    for (Territory *tt : m->getTerritories())
    {
        bool acceptable = true;
        int nbOfAdjacent;

        for (Territory *ii : tt->getAdjTerritories())
        {
            if (ii->getAdjTerritories().size() > 10)
            {
                cout << "Invalid map ! It has " << ii->getAdjTerritories().size() << " adjacent territories to " << ii->getName() << " which is bigger than 10.\n-----------------------------------------------------------------" << endl;
                acceptable = false;
                break;
            }
        }
        if (acceptable == false)
        {
            return false;
        }
    }

    cout << "\n" << m->getFileName() << " is a valid map !\n" << "-----------------------------------------------------------------\n" << endl;
    
    // if it has not return false, then valid map return true
    return true;
}

// MAPLOADER CLASS

// defines the MapLoader constructor with an initilizer list
MapLoader::MapLoader(string fileName) : fileName(fileName),
                                        map(loadMap(fileName)) // as soon as you create a map loader and creates a map by using the loadmap function and the file inputted
{
}
// defines the MapLoader copy constructor with an initilizer list
MapLoader::MapLoader(MapLoader &ml)
{
    map = ml.map;
    fileName = ml.fileName;
}
// Overloaded assignment operator for the MapLoader class definition
MapLoader &MapLoader::operator=(const MapLoader &o)
{

    this->map = o.map;
    this->fileName = o.fileName;

    return *this;
}
// Overloaded Stream insertion operator for the MapLoader class definition
// prints name of the file
ostream &operator<<(ostream &out, MapLoader &o)
{

    out << "Name: " << o.getFileName() << std::endl;
    return out;
}

string MapLoader::getFileName() { return fileName; } // getFileName() definition

Map *MapLoader::getMap() { return map; } // getMap() definition

Map *MapLoader::loadMap(string fileName) // loadMap() definition
{
    // the function allows it to read the file twice, the first one to place all continents and territories into
    // their respective vectors, and the second one to place the adjacent territories into a vector by using
    // the territory vector
    bool firstRead = true;

    // creates a new map object using the filename inputted
    Map *map = new Map(fileName);

    // for loop to read the file twice
    for (int i = 0; i < 2; i++)
    {

        // open the inputted file for reading
        std::ifstream file(fileName);

        // variable to store each line from the file
        string line;

        // state = 0 -> nothing to store, state = 1 -> continents to store, state = 2 -> territories to store
        int state = 0;

        int lineNum = 0;

        // reads through the file line by line
        while (getline(file, line))
        {

            // if the first character has a bracket and 'C', then upcoming lines should be read as continents to store
            if (line[0] == '[' && line[1] == 'C')
            {
                state = 1;
                continue;
            }

            // if the first character has a bracket and 'T', then upcoming lines should be read as territories to store
            if (line[0] == '[' && line[1] == 'T')
            {
                state = 2;
                continue;
            }

            // if the file is read for the first time and state = 1, then store the upcoming continents
            if (state == 1 && firstRead)
            {
                // if line has nothing on it, skip the line
                if (line.length() == 0)
                {
                    continue;
                }

                // seperate the line, and creates a continent object with its name and its bonus in a vector of pointers of type continent
                vector<string> v = splitString(line, '=');

                Continent *c = new Continent(v[0], std::stoi(v[1]));

                map->addContinent(c);
            }

            // if the file is read for the first time and state = 2, then store the upcoming territories
            if (state == 2 && firstRead)
            {
                // if line has nothing on it, skip the line
                if (line.length() == 0)
                {
                    continue;
                }

                // seperate the line, and creates a territory object with its name and its associated continent in two vectors of pointers of type territory
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
            // if the file is read for the second time and state = 2, then store the upcoming territories as adjacent territories of the
            // already stored territories
            else if (state == 2)
            {
                // if line has nothing on it, skip the line
                if (line.length() == 0)
                {
                    continue;
                }
                // seperate the line, and adds adjacent territories in a vector of pointers of type territory for each territory object
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
        file.clear(); // used to reset the state flags of a stream
    }

    return map;
}

vector<string> MapLoader::splitString(string line, char splitter) // splitString function definition where splitter is the char delimiter
{
    string x;
    std::stringstream ss(line); // using the stringstream class for parsing
    vector<string> returnedVector;

    while (getline(ss, x, splitter))
    {

        returnedVector.push_back(x); // adds each string from the line in a vector
    }
    return returnedVector;
}

// FREE FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

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

// laundry List:
// - comment the dfs free functions, validate method, and testloadmap method

// DONE:
// - put all the functions from the mapdriver.cpp into the map.cpp
// - create the validate() function (take whats in the testloadmap and the last part of loadmap)
// - have the testloadmap() take in a verctor of pointers of type map object and use the validate method
// - fix the overloaded stream insertions for pointer objects
// - test out the MapDriver, validate(), assignment operator,and overloaded stream insertions
// - remove the maploader files
