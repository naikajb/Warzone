#ifndef MAP_H // if Map.h file not defined
#define MAP_H // define it

#include <iostream> // import library that provides objects which can read user input and output data to the console or to a file
#include <string> // import library to use string features
#include <vector> //import library to use vectors
#include <list> // import library to use list features
#include <sstream>
#include <fstream>

using std::string; // class template add features support strings
using std::vector; // class template that contains vector container and its member functions
using std::ostream;

class Continent; // class Continent call for the Territory class

class Territory // creation of Territory class
{
private: // access identifier
    string name; 
    int numArmies;
    Continent* continent; //pointer to user-defined class Continent
    vector<Territory *> adjTerritories; // vector of pointers of user-defined type Territory

public: // access identifier
    // Territory parametrized constructor declaration
    Territory(string name, Continent* continent);

    // Territory copy constructor declaration
    Territory(const Territory& t);

    Territory& operator=(Territory& o);

    friend ostream& operator<<(ostream& out, Territory& o);

    string getName(); // Getter Territory names
    int getNumArmies(); // Getter number of armies
    Continent* getContinent(); // Getter Continent
    vector<Territory *> getAdjTerritories(); // Getter adjacent territories

    void setNumArmies(int numArmies); // Setter number of armies
    // void setContinent(string continent); 
    void addAdjTerritories(Territory *adjTerritory); // Add pointer of type Territory as adjacent territories in vector
};

class Continent // creation of Continent class
{

private: // access identifier
    string name;
    int bonus;
    vector<Territory *> territories; // vector of pointers of user-defined type Territory

public: // access identifier
    // Continent paramerized constructor declaration
    Continent(string name, int bonus);

    // Continent copy constructor declaration
    Continent(const Continent&);

    Continent& operator=(Continent& o);

    friend ostream& operator<<(ostream& out, Continent& o);

    string getName(); // Getter Continent names
    int getBonus(); // Getter bonus for each Continent
    vector<Territory *> getTerritories(); // Getter territories part of the Continent

    void addTerritory(Territory *t); // Add pointer of type Territory as territories part of Continent in vector
};

class Map // creation of Map class
{

private: // access identifier
    string fileName; 
    vector<Territory *> territories; // vector of pointers of type Territory
    vector<Continent *> continents; // vector of pointers of type Continent

public: // access identifier
    // Map paramerized constructor declaration
    Map(string fileName);

    // Map copy constructor declaration
    Map(const Map&);

    Map& operator=(Map& o);

    friend ostream& operator<<(ostream& out, Map& o);

    string getFileName();
    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();

    void addTerritory(Territory *t); // Add pointer of type Territory in vector
    void addContinent(Continent *c); // Add pointer of type Continent in vector

    void validate(); // checks if the Map Object is a connected graph, Continents are connected subgraphs and each Country belongs to one and only one Continent
};

class MapLoader {

    private:

    Map* map;
    string fileName;

    public:

    Map(string fileName);

    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();

    void addTerritory(Territory *t); // Add pointer of type Territory in vector
    void addContinent(Continent *c); // Add pointer of type Continent in vector

    void validate(); // checks if the Map Object is a connected graph, Continents are connected subgraphs and each Country belongs to one and only one Continent
};

class MapLoader {

    private:

    Map* map;
    string fileName;

    public:
    
    MapLoader(string fileName);

    MapLoader(MapLoader&);

    MapLoader& operator=(MapLoader& o);

    friend ostream& operator<<(ostream& out, MapLoader& o);

    string getFileName();

    vector<string> splitString(string line, char splitter);

    Map* loadMap(string fileName);

    Map* getMap();
   
};

#endif // end of if not defined statement MAP_H
