#ifndef MAPDRIVER_H
#define MAPDRIVER_H

#include <iostream>

#include "Map.h"


void testLoadMaps();

void DFSHelper(Territory*,vector<Territory*>&);

bool DFS(Map*);

void DFSContinent(Territory*,vector<Territory*>&);

bool DFSC(Continent*);

bool uniqueCountry(Map* map);

int main();

#endif