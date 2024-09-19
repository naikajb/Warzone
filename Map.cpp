#include "Map.h"


Territory::Territory(string name, string continent): 
    name(name), 
    continent(continent)
{
}

string Territory::getName() { return name; }
int Territory::getNumArmies(){ return numArmies; }
string Territory::getContinent(){ return continent; }
vector<Territory*> Territory::getAdjTerritories(){ return adjTerritories; }

void Territory::setNumArmies(int numArmies){ numArmies = numArmies; }
void Territory::setContinent(string continent){ continent = continent; }
void Territory::addAdjTerritories(Territory* adjTerritory){ adjTerritories.push_back(adjTerritory); }


Continent::Continent(string name, int bonus):
    name(name),
    bonus(bonus)
{
}

string Continent::getName(){return name; }
int Continent::getBonus(){ return bonus; }
vector<Territory*> Continent::getTerritories(){ return territories; }

void Continent::addTerritory(Territory* t){ territories.push_back(t);}


Map::Map(string fileName):
    fileName(fileName)
{
}


vector<Territory*> Map::getTerritories(){ return territories; }
vector<Continent*> Map::getContinents(){ return continents; }

void Map::addTerritory(Territory* t){
    territories.push_back(t);
}

void Map::addContinent(Continent* c){
    continents.push_back(c);
}