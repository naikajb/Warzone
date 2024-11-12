#include "CommandProcessor.h"

// Constructor
CommandProcessor::CommandProcessor(Observer* o) {
    Attach(o);
    createMap();
}

// Copy Constructor
CommandProcessor::CommandProcessor(const CommandProcessor& commandProcessor) {
    std::cout << "Copy Constructor of CommandProcessor";
}

// Destructor
CommandProcessor::~CommandProcessor() {
    for (Command* cmd : commands) {
        delete cmd;
        cmd = NULL;
    }
    commands.clear();
    Detach(observer);
}

// Read the command from the input
Command* CommandProcessor::readCommand(std::string& commandstr) {
    Command* command = new Command(commandstr);
    command->Attach(observer);
    //std::cout << "Command is created: " << *command << std::endl;
    return command;
}

// Save the command to the stored vector
void CommandProcessor::saveCommand(Command* cmd) {
    if (cmd != nullptr) {
        commands.push_back(cmd);
        Notify(this);
    } else {
        std::cout << "Error: Command is null!" << std::endl;
    }
}
// Get the command from the input
Command* CommandProcessor::getCommand(std::string& commandstr) {
    Command* cmd = readCommand(commandstr);
    saveCommand(cmd);
    return cmd;
}

// Create the map of commands and states
void CommandProcessor::createMap() {
    commandStateMap.insert(std::make_pair("loadmap", "startState"));
    commandStateMap.insert(std::make_pair("loadmap", "mapLoadedState"));
    commandStateMap.insert(std::make_pair("validatemap", "mapLoadedState"));
    commandStateMap.insert(std::make_pair("addplayer", "mapValidated"));
    commandStateMap.insert(std::make_pair("addplayer", "playersAdded"));
    commandStateMap.insert(std::make_pair("gamestart", "playersAdded"));
    commandStateMap.insert(std::make_pair("replay", "win"));
    commandStateMap.insert(std::make_pair("quit", "win"));
}

// Validate the command with the current state
bool CommandProcessor::validate(Command* cmd, const char* state) {
    // std::cout << "Validating command: " << *cmd << " against state: " << state << std::endl;
    
    std::string commandStr = cmd->getCommandStr();
    auto range = commandStateMap.equal_range(commandStr);

    // iterate over the range to check if any state matches the desired state
    for (auto it = range.first; it != range.second; ++it) {
        if(it->second == state) {
            return true;
            cmd->saveEffect("Command " + commandStr + " is valid for current state " + state);
        }
    }
    cmd->saveEffect("Invalid command " + commandStr + " for current state " + state);
    return false;
}

// Convert the command processor to a string
std::string CommandProcessor::stringToLog() {
    std::string str =  "CommandProcessor is processing command " + commands.back()->getCommandStr()
            + "\n\tpast commands: ";
    for (Command* cmd : commands) {
        str += cmd->getCommandStr() + ", ";
    }
    return str;
            

}