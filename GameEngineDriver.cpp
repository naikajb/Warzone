#include "GameEngine.h"

// free function, it controls the command loop that interacts with the GameEngine through the CommandParser
void testGameStates(GameEngine& engine, CommandParser& parser) {

    std::cout << "Starting Game Engine, Please Type A Command\n";

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

int main() {

    GameEngine engine;
    //passing engine pointer to parser object
    CommandParser parser(&engine);

    testGameStates(engine, parser);

    return 0;
}