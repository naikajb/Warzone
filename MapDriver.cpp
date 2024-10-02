#include "MapDriver.h" // import MapDriver.h header file

vector<Map *> testLoadMaps(vector<Map *> mapSet) // testLoadMaps() definition
{
    // create a vector of pointer of type Map that will only contain valid maps
    vector<Map *> validMaps;
    bool valid = true;

    // go through the inputted vector, if the map is valid, place it in the vector, else ignore map
    for (Map *m : mapSet)
    {
        valid = Map::validate(m);

        if (valid == true)
            validMaps.push_back(m);
    }

    // return a vector with only valid pointers of Map objects
    return validMaps;
}

// program driver
void testLoadMaps()
{

    MapLoader *ml = new MapLoader("MapTextFiles\\South America.map");

    // overloaded stream insertion for map
    cout << *(ml->getMap());

    // overloaded stream insertion for continent
    for (Continent *c : ml->getMap()->getContinents())
    {
        cout << *c << endl;
    }

    // overloaded stream insertion for territory
    for (Territory *t : ml->getMap()->getTerritories())
    {
        cout << *t << endl;
    }

    // deallocates the memory space in the heap where ml is pointing to
    delete ml;
    // ml pointer no longer points to any valid memory
    ml = NULL;
}
