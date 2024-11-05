#ifndef FILE_LINE_READER_H
#define FILE_LINE_READER_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

class FileLineReader {
private:
    std::ifstream fileStream;
    std::string str;
    std::vector<std::string> storedLines;
    std::multimap<std::string, std::string> commandStateMap;
    std::string fileName;
   
public:
    FileLineReader(const std::string& fileName);
    ~FileLineReader();
    std::string getLine();
    std::string readLine();
    void saveLine(std::string line);
    bool validate(std::string line);  
};


#endif