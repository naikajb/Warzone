#include "MapDriver.h"


void testLoadMaps(){

    MapLoader* ml = new MapLoader("Annys World.txt");

    if(DFS(ml->getMap())){

        std::cout << "Map is a connected Graph (V1)." << std::endl;

    }else{

        std::cout << "Map is a NOT connected Graph (V1)." << std::endl;
    }

    bool v2 = true;

    for(Continent* c : ml->getMap()->getContinents()){
        
        if(!DFSC(c)){
            v2 = false;
            break;
        }
    }

    if(v2){

        std::cout << "Continents are connected subgraphs (V2)." << std::endl;

    }else{

        std::cout << "NOT all Continents are connected subgraphs (V2)." << std::endl;
    }


    if(uniqueCountry(ml->getMap())){

        std::cout << "Territories belong to one and only one Continent (V3)." << std::endl;

    }else{

        std::cout << "At least one Territory belongs to more than one Continent (V3)." << std::endl;
    }

}

void DFSHelper(Territory* current, vector<Territory*>& visited) {

    for (Territory* t : current->getAdjTerritories()) {
        bool contained = false;

        for (Territory* t2 : visited) {
            if (t->getName().compare(t2->getName()) == 0) {
                contained = true;
                break;
            }
        }

        if (!contained) {
            visited.push_back(t);
            DFSHelper(t, visited);  
        }
    }
}

bool DFS(Map* map) {
    vector<Territory*> visited;
    visited.push_back(map->getTerritories()[0]);
    DFSHelper(map->getTerritories()[0], visited);  
    return (visited.size() == map->getTerritories().size());
}


void DFSContinent(Territory* current, vector<Territory*>& visited){

    for (Territory* t : current->getAdjTerritories()) {

        if(t->getContinent().compare(current->getContinent()) != 0){
            continue;
        }
        
        bool contained = false;

        for (Territory* t2 : visited) {
            if (t->getName().compare(t2->getName()) == 0) {
                contained = true;
                break;
            }
        }

        if (!contained) {
            visited.push_back(t);
            DFSContinent(t, visited);  
        }
    }
}

bool DFSC(Continent* c){

    vector<Territory*> visited;
    visited.push_back(c->getTerritories()[0]);
    DFSContinent(c->getTerritories()[0],visited);  
    return (visited.size() == c->getTerritories().size());

}


bool uniqueCountry(Map* map){

    for(Territory* t : map->getTerritories()){

        int count(0);

        for(Continent* c: map->getContinents()){

            for(Territory* t2 : c->getTerritories()){

                if(t->getName().compare(t2->getName()) == 0){
                    count+=1;
                }
            }
        }

        if(count>1){
            return false;
        }
    }
    return true;
}

int main(){

    testLoadMaps();

    return 0;
}

// g++ -std=c++11 MapDriver.cpp Map.cpp