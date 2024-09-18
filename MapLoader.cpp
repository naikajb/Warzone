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

    Map* map = new Map();

    ifstream file(fileName);

    if(!file.is_open()){

        std::cout << "Error";
        return NULL;

    }

    string line;

    int state = 0;

    while(getline(file,line)){

        if(line[0] == '[' && line[1] == 'C'){
            state = 1;
        }


        if(line[0] == '[' && line[1] == 'T'){
            state = 2;
        }

        if(state == 1 && line[0] != '['){

            if(line.length()==1){
                continue;
            }

            vector<string> v = splitString(line, '=');

            Continent* c = new Continent(v[0],std::stoi(v[1]));

            map->addContinent(c);

        }

        if(state == 2 && line[0] != '['){

            if(line.length()==1){
                continue;
            }

            vector<string> v = splitString(line, ',');

            bool alreadyListed = false;

            for(Territory* t: map->getTerritories()){

                if(t->getName().compare(v[0]) == 0){ 

                    alreadyListed = true;

                    vector<Territory*> adj;

                    for(int i = 0; i < v.size()-4; i++){
                        adj.push_back(new Territory (v[i+4]));
                        
                        if(!map->territoryExists(adj[i])){
                            map->addTerritory(adj[i]);
                        }
                    }

                    t->setCoordX(std::stoi(v[1]));
                    t->setCoordY(std::stoi(v[2]));
                    t->setContinent(v[3]);
                    t->setAdjTerritories(adj);

                    map->addTerrToCont(t);

                }
            }

            if(!alreadyListed){

                vector<Territory*> adj;

                for(int i = 0; i < v.size()-4; i++){
                        adj.push_back(new Territory (v[i+4]));
                    }

                Territory* t = new Territory(v[0],0,std::stoi(v[1]),std::stoi(v[2]),v[3],adj);
                map->addTerritory(t);
                map->addTerrToCont(t);

            }

        }
    }

    file.close();

    return map;
}

void BFS(Map* map){

    set<Territory*> visited;
    queue<Territory*> queue;

    queue.push(map->getTerritories()[0]);
    
    while(!queue.empty()){

        for(Territory* t: queue.front()->getAdjTerritories()){

            if(visited.find(t) == visited.end()){

                visited.insert(t);
                //queue.push(t); //generates segmentation fault

            }
        }
    }
}

void testLoadMaps(){

    Map* map = createMap("Annys_World.txt");

    //BFS(map);
    

}

int main(){

    testLoadMaps();

    return 0;
}


// g++ -std=c++11 MapLoader.cpp Map.cpp

/*
for(Territory* t: map->getTerritories()){

        std::cout << t->getName() << std::endl;

        std::cout << "-----------------" << std::endl;

        for(Territory* t2: t->getAdjTerritories()){

            std::cout << t2->getName() << std::endl;

        }

        std::cout << std::endl;
        std::cout << std::endl;

   }*/