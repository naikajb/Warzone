#include "Map.h" // import Map.h header file
class Continent; // forward declaration of Continent class

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
    playerOwner = t.playerOwner;
}

// Overloaded assignment operator for the Territory class definition
Territory &Territory::operator=(const Territory &o)
{
    this->name = o.name;
    this->numArmies = o.numArmies;
    this->continent = o.continent;
    this->adjTerritories = o.adjTerritories;
    this->playerOwner = o.playerOwner;

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
Player *Territory::getPlayerOwner() {return playerOwner;}

void Territory::setNumArmies(int numArmies) { this->numArmies = numArmies; } // setNumArmies() definition
void Territory::addAdjTerritories(Territory *adjTerritory) { adjTerritories.push_back(adjTerritory); } // addAdjTerritories() definition
void Territory::setPlayerOwner(Player *p) {playerOwner = p;};

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
// validates a Map 'm' for the 3 required verifications:
//  1. A Map is a connected graph
//  2. Every Continent is a connected subgraph
//  3. Every Territory is only present once in a single Continent
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

void DFSHelper(Territory *current, vector<Territory *> &visited) // main part of the depth first search traversal algorithm to verify that the map is a connected graph
// the 'visited' vector is a reference so that updating it with recursion is possible
{

    for (Territory *t : current->getAdjTerritories()) // iterates through all the adjacent territorys of 'current'
    {
        bool contained = false;

        for (Territory *t2 : visited) // iterates through the Territory objects in the 'visited' vector
        {
            if (t->getName().compare(t2->getName()) == 0) // if an adjacent Territory is already in 'visited'
            {
                contained = true; 
                break; 
            }
        }

        if (!contained)
        {
            visited.push_back(t); // add Territory 't' to the 'visited' vector
            DFSHelper(t, visited); // recursive call
        }
    }
}

bool DFS(Map *map) // method we call from the validate method to check if the map is a connected graph
{
    vector<Territory *> visited; 
    visited.push_back(map->getTerritories()[0]); // push the first Territory added to the Map in the 'visited' vector
    DFSHelper(map->getTerritories()[0], visited); // calls the recursive method DFSHelper and updates the 'visited' vector with recursion
    return (visited.size() == map->getTerritories().size()); // if the size of visited is equal to the number of Territory objects in the Map, we have a connected graph
}

void DFSContinent(Territory *current, vector<Territory *> &visited) // main part of the depth first search traversal algorithm to verify that every Continent object is a connected subgraph
// the 'visited' vector is a reference so that updating it with recursion is possible
{

    for (Territory *t : current->getAdjTerritories()) // iterates through all the adjacent territories of the 'current' Territory
    {

        if (t->getContinent()->getName().compare(current->getContinent()->getName()) != 0) // if the 'current' Territory does not belong to the same Continent as Territory 't', we continue
        {
            continue;
        }

        bool contained = false;

        for (Territory *t2 : visited) // iterates through the 'visited' vector
        {
            if (t->getName().compare(t2->getName()) == 0) // if Territory 't' is already in 'visited', 'contained' is equal to true
            {
                contained = true;
                break; 
            }
        }

        if (!contained)
        {
            visited.push_back(t); // if Territory 't' is not in 'visited', we add it to the vector
            DFSContinent(t, visited); // recursive call
        }
    }
}

bool DFSC(Continent *c) // important note: this method is called for every Continent object and tests each Continent to see if they are connected subgraphs
{

    vector<Territory *> visited;
    visited.push_back(c->getTerritories()[0]); // push the first Territory added to the Continent 'c' in the 'visited' vector
    DFSContinent(c->getTerritories()[0], visited); // calls the recursive method DFSContinent and updates the 'visited' vector with recursion
    return (visited.size() == c->getTerritories().size()); // returns if a given Continent is a connected subgraph with the size comparison of 'visited' and its corresponding Continent size
}

bool uniqueCountry(Map *map) // method to verify if a Territory is unique and is not present in multiple Continent objects
{

    for (Territory *t : map->getTerritories()) // iterates through all the Territory objects of 'map'
    {

        int count(0);

        for (Continent *c : map->getContinents()) // iterates through all the Continent objects of 'map'
        {

            for (Territory *t2 : c->getTerritories()) // iterates through all the Territory objects in Continent 'c'
            {

                if (t->getName().compare(t2->getName()) == 0) // if the Territory 't' is found in a given Continent 'c', we increment 'count' by 1
                {
                    count += 1;
                }
            }
        }

        if (count > 1) // if the count is bigger than 1, a given Territory 't' is present in multiple Continents or present more than once in a Continent 'c'
        {
            return false; // returns that not every Territory is unique
        }
    }
    return true; // returns that every Territory is unique
}
