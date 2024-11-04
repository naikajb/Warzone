#include "FileCommandProcessorAdapter.h"

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const std::string& fileName) : CommandProcessor() {
    fileStream.open(fileName);
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open file: " << fileName << std::endl;
    }
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    fileStream.close();
}

