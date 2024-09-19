#include "MapLoader.h"

vector<string> splitString(string line, char splitter){

    string x;
    std::stringstream ss(line);
    vector<string> returnedVector;

    while(getline(ss,x,splitter)){

        returnedVector.push_back(x);
    }
    return returnedVector;
}

Map* createMap(string fileName){

    bool firstRead = true;

    Map* map = new Map(fileName);

    for(int i = 0; i < 2; i++){

        ifstream file(fileName);

        string line;

        int state = 0;

        int lineNum = 0;

        while(getline(file,line)){

            if(line.length() > 1){

                line.erase(line.size()-1); 

            }

            if(line[0] == '[' && line[1] == 'C'){
                state = 1;
                continue;
            }

            if(line[0] == '[' && line[1] == 'T'){
                state = 2;
                continue;
            }

            if(state == 1 && firstRead){

                if(line.length()==1){
                    continue;
                }

                vector<string> v = splitString(line, '=');

                Continent* c = new Continent(v[0],std::stoi(v[1]));

                map->addContinent(c);

            }

            if(state == 2 && firstRead){

                vector<string> v = splitString(line,',');

                Territory* t = new Territory(v[0],v[3]);

                map->addTerritory(t);

                for(Continent* c: map->getContinents()){

                    if(c->getName().compare(v[3]) == 0){

                        c->addTerritory(t);

                    }
                }

            }else if(state == 2){

                vector<string> v = splitString(line,',');

                for(int j = 0; j < v.size()-4; j++){

                    for(Territory* t: map->getTerritories()){

                        if(v[j+4].compare(t->getName()) == 0){

                            map->getTerritories()[lineNum]->addAdjTerritories(t);
                            break;
                        }
                    }
                }
                lineNum+=1;
            }
        }
        firstRead = false;
        file.clear();
    }
    return map;
}

void DFSHelper(Territory* current, vector<Territory*>& visited) {

    //std::cout << current->getName() << std::endl; // displaying all territories thru DFS

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

void testLoadMaps(){

    Map* map = createMap("001_I72_Ghtroc 720.txt");
    //Map* map = createMap("Annys World.txt");

    if(DFS(map)){

        std::cout << "The map is a connected Graph (Verification 1)." << std::endl;

    }else{

        std::cout << "The map is NOT a connected Graph (Verification 1)." << std::endl;
    }

}

int main(){

    testLoadMaps();

    return 0;
}

// g++ -std=c++11 MapLoader.cpp Map.cpp