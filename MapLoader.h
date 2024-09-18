#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>
#include <queue>

#include "Map.h"

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::set;
using std::queue;

vector<string> splitString(string, char);
Map* createMap(string);
void testLoadMaps();
void BFS(Map* map);

int main();

#endif
