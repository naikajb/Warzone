#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "Command.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class CommandProcessor {
    public:
        CommandProcessor();
        CommandProcessor(const CommandProcessor& commandProcessor);
        virtual ~CommandProcessor();
        Command* getCommand(std::string& commandstr);
        bool validate(Command* cmd, const char* state);
    private:
        Command* readCommand(std::string& commandstr);
        void saveCommand(Command* cmd);
        std::vector<Command*> commands;
        void createMap();
        multimap<std::string, std::string> commandStateMap;
};


#endif