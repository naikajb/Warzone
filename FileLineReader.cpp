#include "FileLineReader.h"
#include <iostream>

FileLineReader::FileLineReader(const std::string& fileName) {
    fileStream.open(fileName);
    if (!fileStream.is_open()) {
        // std::cerr << "Error: Could not open file: " << fileName << std::endl;
        throw std::invalid_argument("Error: Could not open file: " + fileName);
    }
}

FileLineReader::~FileLineReader() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

std::string FileLineReader::readLine() {
    if (fileStream.is_open() && getline(fileStream, str)) {
        return str;
    }
    return "";
}

std::string FileLineReader::getLine() {
    if (fileStream.is_open() && getline(fileStream, str)) {
        saveLine(str);
        return str;
    }
    return "";
}

void FileLineReader::saveLine(std::string line) {
    storedLines.push_back(line);
}

// main() {
//     FileLineReader fileLineReader("commands.txt");
//     std::string line;
//     while ((line = fileLineReader.getLine()) != "") {
//         std::cout << line << std::endl;
//     }
//     return 0;
// }