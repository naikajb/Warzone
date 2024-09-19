#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Map.h"

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;

vector<string> splitString(string, char);
Map* createMap(string);
void testLoadMaps();
void DFSHelper(Territory*,vector<Territory*>&);
bool DFS(Map* map);


int main();

#endif