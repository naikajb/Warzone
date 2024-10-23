#include <iostream>

// Include headers for each part's test function
#include "OrdersDriver.h"
#include "MapDriver.h"
#include "GameEngine.h"
#include "PlayerDriver.h"
#include "CardDriver.h"

int main(int argc, char **argv){

    //if there is more than one argument passed to the program print error message
    if (argc > 2){
        std::cout << "Invalid arguments. \nPlease run the program without any arguments to start the game or with '-test' to run the tests." << std::endl;
        return 0;
    }
    //if one argument passed --> check that it is '-test' to run the tests otherwise print error message
    else if (argc == 2){
        if (strcmp(argv[1], "-test") == 0)
        {
            std::cout << "Running tests..." << std::endl;
            int choice = 0;

            // display the menu
            do
            {
                std::cout << "\nEnter the number of the component you would like to test:" << std::endl;
                std::cout << "1. Map Component" << std::endl;
                std::cout << "2. Player Component" << std::endl;
                std::cout << "3. Orders List Component" << std::endl;
                std::cout << "4. Cards Component" << std::endl;
                std::cout << "5. Game Engine Component" << std::endl;
                std::cout << "Press any other key to exit." << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    // test the map component
                    std::cout << "\nTesting Part 1 - Map Component :" << std::endl;
                    testLoadMaps();
                    break;
                case 2:
                    // test the player component
                    std::cout << "\nTesting Part 2 - Player Component :\n"
                              << std::endl;
                    testPlayers();
                    break;
                case 3:
                    // test the orders list component
                    std::cout << "\nTesting Part 3 - Orders List Component:\n"
                              << std::endl;
                    testOrdersLists();
                    break;
                case 4:
                    // test the cards component
                    std::cout << "\nTesting Part 4 - Cards Component:\n"
                              << std::endl;
                    testCards();
                    break;
                case 5:
                    // test the game engine component
                    std::cout << "\nTesting Part 5 - Game Engine Component:\n"
                              << std::endl;
                    testGameStates();
                    break;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
                    break;
                }
            } while (choice >= 1 && choice <= 5);
        }
        else
        {
             std::cout << "Invalid arguments. \nPlease run the program without any arguments to start the game or with '-test' to run the tests." << std::endl;
        }

        return 0;
    //if no arguments passed --> start the game
    }else{
        
        std::cout << "Starting the game..." << std::endl;
        return 0;
    }
}