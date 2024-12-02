#include "Command.h"
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"

void testCommandProcessor(){
    Observer* obs = new LogObserver();
    CommandProcessor* commandProcessor = new CommandProcessor(obs);
    
    std::string command;
    std::cout << "Enter a command: ";
    std::cin >> command;


    Command* cmd = commandProcessor->getCommand(command);
    std::cout << "Command: " << cmd->stringToLog() << std::endl;
    


}