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
    
}

int main(){
    testPlayers();
    return 0;  
}