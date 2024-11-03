#include "CommandProcessor.h"

//REMEBER TO DELETE POINTER WHEN FUNCTION IS CALLED
Command* CommandProcessor::readCommand() {
    std::string commandstr;
    cin >> commandstr;
    Command* command = new Command(commandstr);
    saveCommand(command);
    return command;
}

void CommandProcessor::saveCommand(Command* cmd) {
    commands.push_back(cmd);
}

Command* CommandProcessor::getCommand() {
    if (!commands.empty()) {
        Command* cmd = commands.back();
        // commands.erase(commands.begin()); // Remove the retrieved command
        return cmd;
    } else {
        // Handle the case where no commands are available
        return nullptr; 
    }
}

void CommandProcessor::validate(Command* cmd) {
   
    
}

CommandProcessor::~CommandProcessor() {
    for (Command* cmd : commands) {
        delete cmd;
        cmd = NULL;
    }
    commands.clear();
}