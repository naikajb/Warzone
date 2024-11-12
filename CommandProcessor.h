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

        std::string stringToLog() override;
    private:
        virtual Command* readCommand(std::string& commandstr);
        virtual void saveCommand(Command* cmd);
        std::vector<Command*> commands;
        void createMap();
        multimap<std::string, std::string> commandStateMap;
};


#endif