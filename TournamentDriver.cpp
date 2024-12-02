#include "GameEngine.h"
#include <iostream>

void testTournament()
{
    Observer *o = new LogObserver();
    GameEngine gm = GameEngine(o);
    std::string input;
    cout << "input command: \n"
         << "tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns> " << std::endl;
    std::getline(std::cin >> std::ws, input);
    std::istringstream iss(input);
    std::string command, argument;
    iss >> command;
    std::getline(iss >> std::ws, argument);
    if (!gm.parseTournamentArguments(argument, gm.tournamentArguments))
    {
        std::cout << "Invalid tournament arguments. Please try again." << std::endl;
    }
    
    gm.tournamentPhase();
    delete o;
}