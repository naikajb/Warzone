#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

class Command {
private:
    std::string cmd;
    std::string effect;
    void saveEffect(const std::string& effect);
public:
    Command(const std::string& command);
    Command(const Command& command);
    virtual ~Command();
};





#endif