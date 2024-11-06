#include "CommandProcessor.h"
#include <fstream>
#include <iostream>

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    std::ifstream fileStream;
    std::string currentCommand;

public:
    FileCommandProcessorAdapter(const std::string& fileName);
    ~FileCommandProcessorAdapter();

    // ~FileCommandProcessorAdapter() {
    //     fileStream.close();
    // }

    Command* getCommand() {
        if (fileStream.is_open()) {
            if (std::getline(fileStream, currentCommand)) {
                return CommandProcessor::getCommand(currentCommand);
            }
        }
        return nullptr;
    }

};