#ifndef PLAYERDRIVER_H
#define PLAYERDRIVER_H

#include "Player.h"
#include <iostream>
#include "Map.h"
#include <string>
using namespace std;

void testPlayers();
void addTerritoriesToPlayers(MapLoader* ml, Player* player1);
void handleChoice(int option, Player* player);
void createOrder(string order, Player* player);

#endif // PLAYERDRIVER.H