#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "Command.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

void testCommandProcessor();
class CommandProcessor: public Subject, public ILoggable {
    public:
        CommandProcessor(Observer* o);
        CommandProcessor(const CommandProcessor& commandProcessor);
        virtual ~CommandProcessor();
        virtual Command* getCommand(std::string& commandstr);
        virtual bool validate(Command* cmd, const char* state);
        multimap<std::string, std::string> commandStateMap;
        std::string stringToLog() override;
        void displayCommands(const std::string& state);
    private:
        virtual Command* readCommand(std::string& commandstr);
        virtual void saveCommand(Command* cmd);
        std::vector<Command*> commands;
        void createMap();
        std::map<std::string, std::vector<std::string>> stateCommands;
        // multimap<std::string, std::string> commandStateMap;
};


#endif