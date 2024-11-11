#include "Command.h"

// Command class implementation
Command::Command(const std::string& command) : commandStr(command), effect("") {
    
}    

// Copy constructor
Command::Command(const Command& command) : commandStr(command.commandStr), effect(command.effect) {
    std::cout << "Copy constructor called for command: " << commandStr << std::endl;
}

// Get the command string
std::string Command::getCommandStr() const {
    //std::cout << "Command observer " << (observer) << std::endl;
    return commandStr;
}

// Overloading the << operator
std::ostream& operator<<(std::ostream& os, const Command& command) {
    os << command.commandStr;
    return os;
}

// Destructor
Command::~Command() {}

// Save the effect of the command
void Command::saveEffect(const std::string& effectStr) {
    effect = effectStr;
    Notify(this);
}

// Get the string to log
std::string Command::stringToLog() {
    return "command " + commandStr + " has been executed. It had the effect: " + effect;
}