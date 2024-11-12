#include "GameEngine.h"
#include <iostream>


// free function, it controls the command loop that interacts with the GameEngine through the CommandParser
/*void testGameStates() { // to accept command-line command, argc is the number of arguments, argv is the array of arguments

    Observer* obs = new LogObserver();
    std::string inputMode;
    bool useConsole = false;
    std::cout << "Welcome to the Game Engine!\n\n" << "Choose a mode to input commands: \n" << "1. Console\n" << "2. File\n" << "\nEnter 1 or 2:\n" << "> ";
    std::cin >> inputMode;

     // Select the appropriate CommandProcessor based on command-line argument
    CommandProcessor* commandProcessor = nullptr;
    FileLineReader* fileLineReader = nullptr;

    if (inputMode == "1") {
        commandProcessor = new CommandProcessor(obs);
        //commandProcessor->Attach(obs);
        useConsole = true;
    } 
    else if (inputMode == "2") {
        std::string fileName;
        while (true) {
            std::cout << "\nEnter the file name: ";
            std::cin >> fileName;
            try {
                fileLineReader = new FileLineReader(fileName);
                commandProcessor = new FileCommandProcessorAdapter(obs,fileLineReader);
                //commandProcessor->Attach(obs);
                break;
            } catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } 
    else {
        std::cerr << "\nInvalid input mode. Exiting..." << std::endl;
        return;
    }

    GameEngine engine =  GameEngine(obs);
    std::cout << "\nStarting Game Engine\n\n";

    std::string input;
    std::string unknown = "";

    while (true) {
        if(useConsole) {
            std::cout << "Type a command " << std::endl;
            std::cout << "> ";
            std::getline(std::cin >> std::ws, input);
            bool temp1 = engine.processConsoleCommand(input, commandProcessor);
            if (input == "exit") {
                break;
            }
        }
        else {
            bool temp2 = engine.processFileCommand(unknown, commandProcessor);
        }
        
        
        // Command* cmd = commandProcessor->getCommand(input);
        // if (!cmd) {
        //     break;
        // }
        
    //     std::cout << "> ";
    //     std::getline(std::cin >> std::ws, input);
        
    //     if (input == "exit") {
    //         break;
    //     }
    //     parser.parseCommand(input);
 }
};*/

void testStartupPhase() {
    Observer* o = new LogObserver();
    GameEngine gm = GameEngine(o);
    gm.startupPhase();
}

// int main() {

//     //testGameStates();
//     testStartupPhase();
    

//     return 0;
// }