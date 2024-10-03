#include "GameEngine.h"

// free function, it controls the command loop that interacts with the GameEngine through the CommandParser
void testGameStates() {

    GameEngine engine;

    //passing engine pointer to parser object
    CommandParser parser(&engine);

    std::cout << "\nStarting Game Engine, Please Type A Command\n\n";

    while (true) {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
        parser.parseCommand(input);
    }
};

// int main() {

//     testGameStates();

//     return 0;
// }