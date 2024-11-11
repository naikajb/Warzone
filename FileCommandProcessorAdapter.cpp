#include "FileCommandProcessorAdapter.h"

// Constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(Observer* o,FileLineReader* fileLine) : fileLineReader(fileLine), CommandProcessor(o) {
    
}

// Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {}

// Read the command from the file
Command* FileCommandProcessorAdapter::readCommand(std::string& command) {
    command = fileLineReader->readLine();
    if (command.empty()) {
        return nullptr;  // No more commands to read
    }
    Command* cmd = new Command(command);
    return cmd;
}

// Get the command from the file
Command* FileCommandProcessorAdapter::getCommand(std::string& commandstr) {
    // std::cout << "Getting command from file..." << std::endl;
    std::string line = fileLineReader->getLine();
    if (line.empty()) {
        return nullptr;  // No more commands to read
    }
    Command* command = new Command(line);
    std::cout << "Command from file: " << command->getCommandStr() << std::endl;
    return command;
}

// Save the command to the stored vector
void FileCommandProcessorAdapter::saveCommand(Command* cmd) {
    fileLineReader->saveLine(cmd->getCommandStr());
    Notify(this);
}

// Validate the command with the current state
bool FileCommandProcessorAdapter::validate(Command* cmd, const char* state) {
    return CommandProcessor::validate(cmd, state);
}