#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using std::string;
using std::vector;
using std::ostream;

class Territory {

    private:

    string name;
    int numArmies;
    string continent;
    vector<Territory*> adjTerritories;

    public:

    Territory(string name, string continent);

    Territory(Territory& t);

    Territory& operator=(Territory& o);

    friend ostream& operator<<(ostream& out, Territory& o);

    string getName();
    int getNumArmies();
    string getContinent();
    vector<Territory*> getAdjTerritories();

    void setNumArmies(int numArmies);

    void setContinent(string continent);
    void addAdjTerritories(Territory* adjTerritory);

};

class Continent {

    private:

    string name;
    int bonus;
    vector<Territory*> territories;

    public:

    Continent(string name, int bonus);

    Continent(Continent&);

    Continent& operator=(Continent& o);

    friend ostream& operator<<(ostream& out, Continent& o);

    string getName();
    int getBonus();
    vector<Territory*> getTerritories();

    void addTerritory(Territory* t);
};

class Map {

    private:

    string fileName;
    vector<Territory*> territories;
    vector<Continent*> continents;

    public:

    Map(string fileName);

    Map(Map&);

    Map& operator=(Map& o);

    friend ostream& operator<<(ostream& out, Map& o);

    string getFileName();
    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();

    void addTerritory(Territory* t);
    void addContinent(Continent* c);
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

#endif

