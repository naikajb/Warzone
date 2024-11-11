#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "LoggingObserver.h"

class Command: public Subject , public ILoggable{
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

    std::string stringToLog() override;
};





#endif