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

    std:cout << "Players created: " << players.size() << std::endl;

    std::cout << "New game starting with " << player1->getPlayerName() 
            << " and " << player2->getPlayerName()
           << endl;

    player1->printPlayer();

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

    cout << player1->getPlayerName() << " has " << player1->toDefend().size() << " territories to defend: " << endl;
    for (Territory* t : player1->toDefend()){
        cout << "\t" << t->getName() << endl;
    }

    cout << player2->getPlayerName() << " has " << player2->toAttack().size() << " territories they could attack" << endl;
    for (Territory* t : player2->toAttack()){
        cout << "\t" << t->getName() << endl;
    }

    int orderType = 0, orderNumber = 0;
    while(orderType != -1){
        cout << "Enter order type for " << player1->getPlayerName() << " \n1 for deploy, \n2 for advance, \n3 for bomb, \n4 for blockade, \n5 for airlift, \n6 for negotiate \n-1 to exit \n choice: ";
        cin >> orderType;
        switch(orderType){
            orderNumber++;
            case 1:
                cout << "Enter number of armies to deploy: ";
                cin >> orderNumber;
                player1->issueOrder(new Deploy());
                break;
            case 2:
                cout << "Enter number of armies to advance: ";
                cin >> orderNumber;
                player1->issueOrder(new Advance());
                break;
            case 3:
                player1->issueOrder(new Bomb());
                break;
            case 4:
                player1->issueOrder(new Blockade());
                break;
            case 5:
                cout << "Enter number of armies to airlift: ";
                cin >> orderNumber;
                player1->issueOrder(new Airlift());
                break;
            case 6:
                player1->issueOrder(new Negotiate());
                break;
            default:
                cout << "Invalid order type" << endl;
                break;
        }
    }
    //cout << "Enter order type for " << player1->getPlayerName() << " (1 for deploy, 2 for advance, 3 for bomb, 4 for blockade, 5 for airlift, 6 for negotiate): ";
}


int main(){
    testPlayers();
    return 0;  
}