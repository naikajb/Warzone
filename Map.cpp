#include "Map.h" // import Map.h header file

class Continent; // class Continent call for the Territory class

// defines the Territory constructor with an initilizer list
Territory::Territory(string name, Continent* continent): 
    name(name), 
    continent(continent)
{}
// defines the Territory copy constructor with an initilizer list
Territory::Territory(const Territory &t):
    name(t.name), 
    continent(t.continent)
{}

string Territory::getName() { return name; } // getName() definition
int Territory::getNumArmies(){ return numArmies; } // getNumArmies() definition
Continent* Territory::getContinent(){ return continent; } // getContinent() definition
vector<Territory*> Territory::getAdjTerritories(){ return adjTerritories; } // getAdjTerritories() definition

void Territory::setNumArmies(int numArmies){ numArmies = numArmies; } // setNumArmies() definition
// void Territory::setContinent(string continent){ continent = continent; }
void Territory::addAdjTerritories(Territory* adjTerritory){ adjTerritories.push_back(adjTerritory); } // addAdjTerritories() definition

// defines the Continent constructor with an initilizer list
Continent::Continent(string name, int bonus):
    name(name),
    bonus(bonus)
{}
// defines the Continent copy constructor with an initilizer list
Continent::Continent(const Continent& c):
    name(c.name),
    bonus(c.bonus)
{}

string Continent::getName(){return name; } // getName() definition
int Continent::getBonus(){ return bonus; } // getBonus() definition
vector<Territory*> Continent::getTerritories(){ return territories; } // getTerritories definition

void Continent::addTerritory(Territory* t){ territories.push_back(t);} // addTerritory definition

// defines the Map constructor with an initilizer list
Map::Map(string fileName):
    fileName(fileName)
{}
// defines the Map copy constructor with an initilizer list
Map::Map(const Map& m):
    fileName(m.fileName)
{}

vector<Territory*> Map::getTerritories(){ return territories; } // getTerritories definition
vector<Continent*> Map::getContinents(){ return continents; } // getContinents definition

void Map::addTerritory(Territory* t){ // addTerritory definition
    territories.push_back(t);
}

void Map::addContinent(Continent* c){ // addContinent definition
    continents.push_back(c);
}

void validate(){ // validate() definition

}