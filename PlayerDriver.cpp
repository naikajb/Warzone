#include "Player.h"
using namespace std; 

void testPlayers(){
    vector<Player* > players;

    std::cout << "Enter player 1 name: "; 
    std::string playerName; 
    std::cin >> playerName;
    Player* player1 = new Player(playerName);
    players.push_back(player1);

    std::cout << "Enter player 2 name: ";  
    std::cin >> playerName;
    Player* player2 = new Player(playerName);
    players.push_back(player2);

    std:cout << players.size() <<  " players were created" << std::endl;

    std::cout << "New game starting with " << player1->getPlayerName() 
            << " and " << player2->getPlayerName()
           << endl;

    //player1->printPlayer();

    MapLoader ml("MapTextFiles//USA.map"); 
    // cout << "\n\nThere are currently " << ml.getMap()->getContinents().size() <<  " continents" << endl;
    // cout << "There are currently " << ml.getMap()->getTerritories().size() << " territories" << endl;
    
    player1->addTerritory(ml.getMap()->getTerritories()[0]);
    player1->addTerritory(ml.getMap()->getTerritories()[1]);
    player1->addTerritory(ml.getMap()->getTerritories()[2]);
    player1->addTerritory(ml.getMap()->getTerritories()[3]);
    player1->addTerritory(ml.getMap()->getTerritories()[4]);

    player2 -> addTerritory(ml.getMap()->getTerritories()[5]);
    player2 -> addTerritory(ml.getMap()->getTerritories()[6]);
    player2 -> addTerritory(ml.getMap()->getTerritories()[7]);
    player2 -> addTerritory(ml.getMap()->getTerritories()[8]);
    player2 -> addTerritory(ml.getMap()->getTerritories()[9]);

   
    int orderType = 0, orderNumber = 0;
    cout << "test: " << *player2 << endl;


    delete player1;
    delete player2;
   
}

int main(){
    testPlayers();
    return 0;  
}