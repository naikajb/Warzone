#include "Map.h"


Territory::Territory(string name, int numArmies, int coordX, int coordY, string continent, vector<Territory*> adjTerritories): 
    name(new string(name)), 
    numArmies(new int(numArmies)),
    coordX(new int(coordX)),
    coordY(new int(coordY)),
    continent(new string(continent)),
    adjTerritories(new vector<Territory*>(adjTerritories))
{
}

Territory::Territory(string name):
    name(new string(name))
{
}

string Territory::getName() { return *name; }
int Territory::getNumArmies(){ return *numArmies; }
int Territory::getCoordX(){ return *coordX; }
int Territory::getCoordY(){ return *coordY; }
string Territory::getContinent(){ return *continent; }
vector<Territory*> Territory::getAdjTerritories(){ return *adjTerritories; }

void Territory::setNumArmies(int numArmies){ numArmies = numArmies; }
void Territory::setCoordX(int coordX){ coordX = coordX; }
void Territory::setCoordY(int coordY){ coordY = coordY; }
void Territory::setContinent(string continent){ continent = continent; }
void Territory::setAdjTerritories(vector<Territory*> adjTerritories){ adjTerritories = adjTerritories; }




Continent::Continent(string name, int bonus):
    name(new string(name)),
    bonus(new int(bonus)),
    territories(new vector<Territory*>())
{
}

string Continent::getName(){return *name; }
int Continent::getBonus(){ return *bonus; }
vector<Territory*> Continent::getTerritories(){ return *territories; }

void Continent::addTerritory(Territory* t){ territories->push_back(t);}





int main(){

    Continent* c = new Continent("Continent1",5);

    Territory* t = new Territory("Terr1");
    Territory* t2 = new Territory("Terr2");

    c->addTerritory(t);
    c->addTerritory(t2);



    std::cout << c->getTerritories().at(1)->getName() << std::endl;

    return 0;
}
