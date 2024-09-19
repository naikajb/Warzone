#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;

class Territory {

    private:

    string name;
    int numArmies;
    string continent;
    vector<Territory*> adjTerritories;

    public:

    Territory(string name, string continent);

    //Territory(Territory t); copy constructor ??

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

    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();

    void addTerritory(Territory* t);
    void addContinent(Continent* c);
};

#endif

