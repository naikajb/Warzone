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
        Command* getCommand();
        void validate(Command* cmd);
        multimap<
    private:
        Command* readCommand();
        void saveCommand(Command* cmd);
        std::vector<Command*> commands{};
};


#endif