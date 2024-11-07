//#include "GameEngine.h"
//#ifndef 

// free function, it controls the command loop that interacts with the GameEngine through the CommandParser
#include "GameEngine.h"
void testGameStates() {

    GameEngine engine;
    std::cout << "\nStarting Game Engine, Please Type A Command\n\n";
    std::string input;
    while (true) {
        
        std::cout << "> ";
        std::getline(std::cin >> std::ws, input);
        
        if (input == "exit") {
            break;
        }
        engine.processCommand(input);
    }
    

    

    
    //passing engine pointer to parser object
    // CommandParser parser(&engine);

    // std::cout << "\nStarting Game Engine, Please Type A Command\n\n";
    // std::string input;
    // while (true) {
        
    //     std::cout << "> ";
    //     std::getline(std::cin >> std::ws, input);
        
    //     if (input == "exit") {
    //         break;
    //     }
    //     parser.parseCommand(input);
    // }
};

int main() {

    //testGameStates();
    GameEngine ge;
    ge.startupPhase();





    return 0;
}