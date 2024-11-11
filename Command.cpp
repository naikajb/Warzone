#include "Command.h"

Command::Command(const std::string& command) : commandStr(command), effect("") {
    
}    

Command::Command(const Command& command) : commandStr(command.commandStr), effect(command.effect) {
    std::cout << "Copy constructor called for command: " << commandStr << std::endl;
}

std::string Command::getCommandStr() const {
    //std::cout << "Command observer " << (observer) << std::endl;
    return commandStr;
}
std::ostream& operator<<(std::ostream& os, const Command& command) {
    os << command.commandStr;
    return os;
}

Command::~Command() {}

void Command::saveEffect(const std::string& effectStr) {
    effect = effectStr;
    Notify(this);
}

std::string Command::stringToLog() {
    return "command " + commandStr + " has been executed. It had the effect: " + effect;
}