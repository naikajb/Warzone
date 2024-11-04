#include "PlayerDriver.h"
using namespace std; 

void testPlayers(){
    vector<Player* > players;

    std::cout << "Enter player 1 name: "; 
    std::string playerName; 
    std::cin >> playerName;
    Player* player1 = new Player(playerName);
    players.push_back(player1);

    // std::cout << "Enter player 2 name: ";  
    // std::cin >> playerName;
    // Player* player2 = new Player(playerName);
    // players.push_back(player2);

    //std:cout << players.size() <<  " players were created" << std::endl;

    std::cout << "New game starting with " << player1->getPlayerName() 
                /*<< " and " << player2->getPlayerName() */ << endl;

    MapLoader ml("MapTextFiles//USA.map"); 
    addTerritoriesToPlayers(&ml, player1);

    int option = 0;
    while (option != -1){
        cout << "\nOption Menu" << endl;
        cout << "1. Print the " << players.size() << " players info." << endl; 
        cout << "2. Issue an order." << endl;
        cout << "3. See territories to defend." << endl;
        cout << "4. See territories to attack." << endl;
        cout << "Enter -1 to exit.\nChoice:";
        cin >> option;
        handleChoice(option, player1);
    }

    //cout << *player2 << endl;
    //cout << *player1 << endl;
    //delete player1;
    //delete player2; 
}

void addTerritoriesToPlayers(MapLoader* ml, Player* player){
    for(int i = 0; i < 10; i++){
        if(i % 2 == 0){
            player->addTerritory(ml->getMap()->getTerritories()[i]);
        }
    }
}

void handleChoice(int option, Player* player){
    switch(option){
        case 1:
            cout << *player << endl;
            break;
        case 2:{
            //take in string input to issue order
            string order;
            cout << "Enter order (deploy, advance,bomb, blockade, airlift, and negotiate): " << endl;
            cin >> order;
            createOrder(order, player);
            break;
        }
        case 3:{
            vector<Territory*> t = player->toDefend();
            cout << "\nThese are the " << t.size() << " territories " << player->getPlayerName() << " should defend:" << endl;
            for(int i = 0; i < t.size(); i++){
                cout << t[i]->getName() << endl;
            }
            break;
        }
        case 4:{
            vector<Territory*> t =  player->toAttack();
            cout << "\nThese are the " << t.size() << " territories " << player->getPlayerName() << " could attack:" << endl;
            for(int i = 0; i < t.size(); i++){
                cout << t[i]->getName() << endl;
            }
            break;
        }
        default:
            cout << "\nExiting...." << endl;
            break;
    }
}

void createOrder(string order, Player* player){
    if(order == "deploy"){
        Deploy d = Deploy();
        player->issueOrder(&d);
    }
    else if(order == "advance"){
        Advance a = Advance();
        player->issueOrder(&a);
    }
    else if(order == "bomb"){
        Bomb b = Bomb();
        player->issueOrder(&b);
    }
    else if(order == "blockade"){
        Blockade b = Blockade();
        player->issueOrder(&b);
    }
    else if(order == "airlift"){
        Airlift a = Airlift();
        player->issueOrder(&a);
    }
    else if(order == "negotiate"){
        Negotiate n = Negotiate();
        player->issueOrder(&n);
    }
    else{
        cout << "Invalid order." << endl;
    }
}
// int main(){
//     testPlayers();
//     return 0;  
// }