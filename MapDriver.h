#ifndef MAPDRIVER_H
#define MAPDRIVER_H

#include <iostream>
#include <vector>

using std::vector;

#include "Map.h"

// receives a list of pointers of type map, returns a new list of pointers of type map but with only the valid maps
vector<Map *> testLoadMaps(vector<Map *> mapSet);

int main();

#endif