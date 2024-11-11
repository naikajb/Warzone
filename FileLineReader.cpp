#include "FileLineReader.h"
#include <iostream>

// Constructor
FileLineReader::FileLineReader(const std::string& fileName) {
    fileStream.open(fileName);
    if (!fileStream.is_open()) {
        // std::cerr << "Error: Could not open file: " << fileName << std::endl;
        throw std::invalid_argument("Error: Could not open file: " + fileName);
    }
}

// Destructor
FileLineReader::~FileLineReader() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

// Read the line from the file
std::string FileLineReader::readLine() {
    if (fileStream.is_open() && getline(fileStream, str)) {
        return str;
    }
    return "";
}

// Get the line from the file
std::string FileLineReader::getLine() {
    std::cout << "Getting line from file..." << std::endl;
    if (fileStream.is_open() && getline(fileStream, str)) {
        std::cout << "Line: " << str << std::endl;
        saveLine(str);
        return str;
    }
    return "";
}

// Save the line to the storedLines vector
void FileLineReader::saveLine(std::string line) {
    storedLines.push_back(line);
}
