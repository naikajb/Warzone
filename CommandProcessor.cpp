#include "CommandProcessor.h"

CommandProcessor::CommandProcessor() {
    createMap();
}

CommandProcessor::CommandProcessor(const CommandProcessor& commandProcessor) {
    std::cout << "Copy Constructor of CommandProcessor";
}

CommandProcessor::~CommandProcessor() {
    for (Command* cmd : commands) {
        delete cmd;
        cmd = NULL;
    }
    commands.clear();

}

//REMEBER TO DELETE POINTER WHEN FUNCTION IS CALLED
Command* CommandProcessor::readCommand(std::string& commandstr) {
    Command* command = new Command(commandstr);
    command->Attach(observer);
    return command;
}

void CommandProcessor::saveCommand(Command* cmd) {
    if (cmd != nullptr) {
        commands.push_back(cmd);
        Notify(this);
    } else {
        std::cout << "Error: Command is null!" << std::endl;
    }
}

Command* CommandProcessor::getCommand(std::string& commandstr) {
    Command* cmd = readCommand(commandstr);
    saveCommand(cmd);
    return cmd;
}

void CommandProcessor::createMap() {
    commandStateMap.insert(std::make_pair("loadmap", "startState"));
    commandStateMap.insert(std::make_pair("loadmap", "mapLoadedState"));
    commandStateMap.insert(std::make_pair("validatemap", "mapLoadedState"));
    commandStateMap.insert(std::make_pair("addplayer", "mapValidated"));
    commandStateMap.insert(std::make_pair("addplayer", "playersAdded"));
    commandStateMap.insert(std::make_pair("gamestart", "playersAdded"));
    commandStateMap.insert(std::make_pair("replay", "win"));
    commandStateMap.insert(std::make_pair("quit", "win"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("assigncountries"), "playersAdded"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("issueorder"), "assignReinforcement"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("execorder"), "issueOrders"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("endexecorders"), "executeOrders"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("win"), "executeOrders"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("play"), "win"));
    // commandStateMap.insert(pair<Command*, std::string>(new Command("end"), "win"));
}

bool CommandProcessor::validate(Command* cmd, const char* state) {
    std::cout << "Validating command: " << *cmd << " against state: " << state << std::endl;
    
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

std::string CommandProcessor::stringToLog() {
    std::string log = "CommandProcessor: ";
    for (Command* cmd : commands) {
        log += cmd->stringToLog() + "\n";
    }
    return log;
}