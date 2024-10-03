#ifndef MAPDRIVER_H // if MapDriver.h file not defined
#define MAPDRIVER_H // define it

#include "Map.h" // import Map.h header file
#include <iostream> // import library that provides objects which can read user input and output data to the console or to a file
#include <vector> // import library to use vectors

using std::vector; // class template that contains vector container and its member functions
using std::cout; // class template from the iostream that display the output to the standard output device
using std::endl; // class template that inserts a new-line character

// receives a list of pointers of type map, returns a new list of pointers of type map but with only the valid maps
vector<Map *> testLoadMaps(vector<Map *> mapSet);

// runs the testLoadMaps() with an example of a vector of maps
void testLoadMaps();

#endif // end of if not defined statement MAPDRIVER_H