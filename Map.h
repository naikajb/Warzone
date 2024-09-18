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

    string* name;
    int* numArmies;
    int* coordX;
    int* coordY;
    string* continent;
    vector<Territory*>* adjTerritories;


    public:

    Territory(string name, int numArmies, int coordX, int coordY, string continent, vector<Territory*> adjTerritories);
    Territory(string name);

    //Territory(Territory t); copy constructor ??

    string getName();
    int getNumArmies();
    int getCoordX();
    int getCoordY();
    string getContinent();
    vector<Territory*> getAdjTerritories();

    void setNumArmies(int numArmies);
    void setCoordX(int coordX);
    void setCoordY(int coordY);
    void setContinent(string continent);
    void setAdjTerritories(vector<Territory*> adjTerritories);

};

class Continent {

    private:

    string* name;
    int* bonus;
    vector<Territory*>* territories;

    public:

    Continent(string name, int bonus);

    string getName();
    int getBonus();
    vector<Territory*> getTerritories();

    void addTerritory(Territory* t);

    
};

class Map {

    private:

    vector<Territory*>* territories;
    vector<Continent*>* continents;

    public:

    Map();

    vector<Territory*> getTerritories();
    vector<Continent*> getContinents();

    void addTerritory(Territory* t);
    void addContinent(Continent* c);

    bool territoryExists(Territory *t);

    void addTerrToCont(Territory *t);
};

#endif


