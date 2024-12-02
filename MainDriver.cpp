// #include <iostream>

// // Include headers for each part's test function
#include "OrdersDriver.h"
#include "LoggingObserver.h"
#include "GameEngine.h"

#include "MapDriver.h"
// #include "GameEngine.h"
// #include "PlayerDriver.h"
// #include "CardDriver.h"
#include <cstring>

int main(int argc, char **argv)
{
    // if there is more than one argument passed to the program print error message
    if (argc > 2)
    {
        std::cout << "Invalid arguments. \nPlease run the program without any arguments to start the game or with '-test' to run the tests." << std::endl;
        return 0;
    }
    // if one argument passed --> check that it is '-test' to run the tests otherwise print error message
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-test") == 0)
        {
            std::cout << "Running tests..." << std::endl;
            int choice = 0;
            bool running = true;

            // display the menu
            do
            {
                std::cout << "Welcome Warzone Testing Menu:" << std::endl;
                std::cout << "\nEnter the number of the component you would like to test:" << std::endl;
                std::cout << "1. Game Startup Phase" << std::endl;
                std::cout << "2. Game Play Phase" << std::endl;
                std::cout << "3. Order Execution Implementation" << std::endl;
                std::cout << "4. Game Log Observer" << std::endl;
                std::cout << "5. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                // Validate the input
                if (std::cin.fail())
                {
                    std::cin.clear(); // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                    std::cout << "Invalid input. Please enter a number between 1 and 5." << std::endl;
                    continue; // Prompt the menu again
                }

                switch (choice)
                {
                case 1:
                    // test the game startup phase
                    std::cout << "\nTesting Part 1 - Game Startup Phase:\n"
                              << "--------------------------------------\n"
                              << std::endl;
                    testStartupPhase();
                    break;
                case 2:
                    // test the player component
                    std::cout << "\nTesting Part 2 - Game Play Implementation :\n--------------------------------------\n"
                              << std::endl;

                    break;
                case 3:
                    // test the orders list component
                    std::cout << "\nTesting Part 3 - Order Execution Implemetation :\n--------------------------------------\n"
                              << std::endl;
                    testOrderExecution();
                    break;
                case 4:
                    // test the game log observer
                    std::cout << "\nTesting Part 4 - Game Log Observer\n--------------------------------------\n"
                              << std::endl;
                    testLoggingObserver();
                    break;
                case 5:
                    // exit the program
                    std::cout << "Exiting the program..." << std::endl;
                    running = false;
                    break;

                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                    break;
                }
            } while (running);
            // while (choice != 5);
            // while (choice >= 1 && choice <= 5);
        }
        else
        {
            std::cout << "Invalid arguments. \nPlease run the program without any arguments to start the game or with '-test' to run the tests." << std::endl;
        }

        return 0;
        // if no arguments passed --> start the game
    }
    else
    {

        std::cout << "Starting the game..." << std::endl;
        return 0;
    }
}