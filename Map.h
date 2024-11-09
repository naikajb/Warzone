#ifndef MAP_H // if Map.h file not defined
#define MAP_H // define it

#include "Player.h"

#include <iostream> // import library that provides objects which can read user input and output data to the console or to a file
#include <string>   // import library to use string features
#include <vector>   // import library to use vectors
#include <list>     // import library to use list features
#include <sstream>  // import library to use string streams
#include <fstream>  // import library to input and output stream class to operate on files

using std::cout;    // class template from the iostream that display the output to the standard output device
using std::endl;    // class template that inserts a new-line character
using std::ostream; // class template that contains output stream objects to perform output operations
using std::string;  // class template add features support strings
using std::vector;  // class template that contains vector container and its member functions
class Continent;     // forward declaration of Continent class
class Player;
class Player; // added

class Territory // creation of Territory class
{
private: // access identifier
    string name;
    int numArmies;
    Continent *continent;               // pointer to user-defined class Continent
    vector<Territory *> adjTerritories; // vector of pointers of user-defined type Territory

    Player *playerOwner; // added

public: // access identifier
    // Territory parametrized constructor declaration
    Territory(string name, Continent *continent);

    ~Territory();

    // Territory copy constructor declaration
    Territory(const Territory &t);

    // Overloaded assignment operator for the Territory class declaration
    // (allows assignment of one Territory object to another with "=" operator)
    Territory &operator=(const Territory &o);

    // Overloaded Stream insertion operator for the Territory class declaration
    // (allows to output the details of a Territory object using std::cout or any other output stream)
    friend ostream &operator<<(ostream &out, Territory &o);

    string getName();                        // Getter Territory names
    int getNumArmies();                      // Getter number of armies
    Continent *getContinent();               // Getter Continent
    vector<Territory *> getAdjTerritories(); // Getter adjacent territories
    Player *getPlayerOwner(); //  added

    void setNumArmies(int numArmies); // Setter number of armies
    void addAdjTerritories(Territory *adjTerritory); // Add pointer of type Territory as adjacent territories in vector
    void setPlayerOwner(Player *p); // added
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

    ~Continent();

    // Continent copy constructor declaration
    Continent(const Continent &c);

    // Overloaded assignment operator for the Continent class declaration
    Continent &operator=(const Continent &o);

    // Overloaded Stream insertion operator for the Continent class declaration
    friend ostream &operator<<(ostream &out, Continent &o);

    string getName();                     // Getter Continent names
    int getBonus();                       // Getter bonus for each Continent
    vector<Territory *> getTerritories(); // Getter territories part of the Continent

    void addTerritory(Territory *t); // Add pointer of type Territory as territories part of Continent in vector
};

class Map // creation of Map class
{

private: // access identifier
    string fileName;
    vector<Territory *> territories; // vector of pointers of type Territory
    vector<Continent *> continents;  // vector of pointers of type Continent

public: // access identifier
    // Map paramerized constructor declaration
    Map(string fileName);

    ~Map();

    // Map copy constructor declaration
    Map(const Map &m);

    // Overloaded assignment operator for the Map class declaration
    Map &operator=(const Map &o);

    // Overloaded Stream insertion operator for the Map class declaration
    friend ostream &operator<<(ostream &out, Map &o);

    string getFileName();                 // Getter map file name
    vector<Territory *> getTerritories(); // Getter territories part of the Map
    vector<Continent *> getContinents();  // Getter continents part of the Map

    void addTerritory(Territory *t); // Add pointer of type Territory in vector
    void addContinent(Continent *c); // Add pointer of type Continent in vector

    static bool validate(Map *m); // checks if the Map Object is a connected graph, Continents are connected subgraphs and each Country belongs to one and only one Continent (declaration)
};

class MapLoader // creation of MapLoader class
{

private:      // access identifier
    Map *map; // pointer to user-defined class Map
    string fileName;

public: // access identifier
    // MapLoader paramerized constructor declaration
    MapLoader(string fileName);

    ~MapLoader();

    // MapLoader copy constructor declaration
    MapLoader(MapLoader &ml);

    // Overloaded assignment operator for the MapLoader class declaration
    MapLoader &operator=(const MapLoader &o);

    // Overloaded Stream insertion operator for the MapLoader class declaration
    friend ostream &operator<<(ostream &out, MapLoader &o);

    string getFileName(); // Getter map file name

    vector<string> splitString(string line, char splitter); // function that allows to split strings for every line of the file and returns a vector of string

    Map *loadMap(string fileName); // function to create a Map object using the map file as a parameter

    Map *getMap(); // Getter Map object
};



/////////////////////////////////////////////////

// Free Functions

void DFSHelper(Territory *, vector<Territory *> &);

bool DFS(Map *);

void DFSContinent(Territory *, vector<Territory *> &);

bool DFSC(Continent *);

bool uniqueCountry(Map *map);

#endif // end of if not defined statement MAP_H
