#include "FileCommandProcessorAdapter.h"


FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* fileLine) : fileLineReader(fileLine) {
}


FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    
}
Command* FileCommandProcessorAdapter::readCommand(std::string& command) {
    command = fileLineReader->readLine();
    if (command.empty()) {
        return nullptr;  // No more commands to read
    }
    Command* cmd = new Command(command);
    return cmd;
}

Command* FileCommandProcessorAdapter::getCommand(std::string& commandstr) {
    std::cout << "Getting command from file..." << std::endl;
    std::string line = fileLineReader->getLine();
    if (line.empty()) {
        return nullptr;  // No more commands to read
    }
    Command* command = new Command(line);
    std::cout << "Command: " << command->getCommandStr() << std::endl;
    return command;
}

void FileCommandProcessorAdapter::saveCommand(Command* cmd) {
    fileLineReader->saveLine(cmd->getCommandStr());
}

bool FileCommandProcessorAdapter::validate(Command* cmd, const char* state) {
    return CommandProcessor::validate(cmd, state);
}