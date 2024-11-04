#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

class Command {
private:
    std::string commandStr;
    std::string effect;
    
public:
    Command(const std::string& command);
    Command(const Command& command);
    void saveEffect(const std::string& effectStr);
    virtual ~Command();
    std::string getCommandStr() const;
    friend std::ostream& operator<<(std::ostream& os, const Command& command); //overloading the << operator
};





#endif