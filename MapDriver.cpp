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

// called in program driver as an example of the testLoadMaps() function
void testLoadMaps()
{

    MapLoader *ml = new MapLoader("MapTextFiles\\South America.map");
    MapLoader *ml1 = new MapLoader("MapTextFiles\\USA.map");
    MapLoader *ml2 = new MapLoader("MapTextFiles\\Asia 1200.map"); // invalid map test

    vector<Map *> allMapList;
    vector<Map *> validMapList;

    allMapList.push_back(ml->getMap());
    allMapList.push_back(ml1->getMap());
    allMapList.push_back(ml2->getMap());

    validMapList = testLoadMaps(allMapList);

    cout << "all maps: \n";

    for (Map *am : allMapList)
    {
        cout << am->getFileName() << endl;
    }
    cout << "\nvalid maps: \n";
    for (Map *vm : validMapList)
    {
        cout << vm->getFileName() << endl;
    }

    // deallocates the memory space in the heap where ml, ml1, ml2 is pointing to
    delete ml, ml1, ml2;
    // ml, ml1, ml2 pointer no longer points to any valid memory
    ml = nullptr;
    ml1 = nullptr;
    ml2 = nullptr;
}
