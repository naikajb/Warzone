/** You must deliver a driver as a free function named testLoggingObserver() that demonstrates that (1) The
Command, CommandProcessor (see Part 1), Order, OrderList, and GameEngine classes are all a subclass of the
Subject and ILoggable classes (2) the CommandProcessor::saveCommand(), Order::execute(),
Command::saveEffect(), OrderList::addOrder(), and GameEngine::transition() methods are effectively
using the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file (3) the
gamelog.txt file gets correctly written into when commands are entered on the console (4) when an order is
added to the order list of a player, the game log observer is notified which results in outputting the order to the log
file (5) when an order is executed, the game log observer is notified which results in outputting the effect of the
order to the log file (6) when the GameEngine changes its state, the new state is output to the log file. This driver
function must be in the LoggingObserverDriver.cpp file.*/

/** LoggingObserver Driver 
 *  1 - demonstrates that Command, CommandProcessor, Order, OrderList, and GameEngine are all subclasses of Subject and ILoggable
 *  2 - CommandProcessor::saveCommand(), Order::execute(), Command::saveEffect(), OrderList::addOrder(), and GameEngine::transition() 
 *      effectively using the Notify(Subject) to trigger entries to the log file 
 *  3 - log file gets written to when commands are entered in the console 
 *  4 - when order is added to the order list of a player, the game log observer is notified and outputs the order to the log file
 *  5 - when order is executed, the game log observer is notified and outputs the effect of the order to the log file
 *  6 - when the GameEngine changes its state, the new state is output to the log file 
 * 
 */
#include "LoggingObserver.h"
#include "GameEngine.h"
#include "Orders.h"
#include "Player.h"
#include <typeinfo>
using namespace std;

void testLoggingObserver(){
   LogObserver* observer = new LogObserver();
    GameEngine* engine = new GameEngine(observer);
    Continent* c = new Continent("c", 10);
    Territory* t = new Territory("t", c);
    Territory* t2 = new Territory("t2", c);
    c->addTerritory(t);
    c->addTerritory(t2);

    
    Player* player = new Player("naika", observer);
    OrdersList* orders = new OrdersList(observer);

    Deploy* order = new Deploy(player, 10, t, observer);
    Advance* order2 = new Advance(player, 10, t, t2, observer);

    // Example of observer notified when command is executed
    cout << "\nExample of the observer being notified when an order is executed\n----------------------------------------------" 
        << "\n\texecuting order->execute();"
        << "\n\texecuting order2->execute();"
        << endl;
    order->executeOrder();
    order2->executeOrder();

    // Example of observer notified when order is added to the order list of a player
    cout << "\nExample of the observer being notified when an order is added to the order list of a player\n----------------------------------------------" 
        << "\n\torders->addOrder(order);"
        << "\n\torders->addOrder(order2);"
        << endl;
    // player->issueOrder(order);
    // player->issueOrder(order2);
    
    // Example of observer notified when GameEngine changes its state
    cout << "\nExample of the observer being notified when the GameEngine changes its state\n----------------------------------------------" 
         << "\n\tCommand* loadCommmand = new Command(\"loadmap MapTextFiles/UK.map\");"
            << "\n\tengine->stateTransition(loadCommmand);"
            << "\n\tCommand* validateCommand = new Command(\"validatemap\");"
            << "\n\tengine->stateTransition(validateCommand);"
            << "\n\tCommand* addPlayerCommand = new Command(\"addplayer Trump\");"
            << "\n\tengine->stateTransition(addPlayerCommand);"
            << "\n\tCommand* addPlayerCommand2 = new Command(\"addplayer Harris\");"
            << "\n\tengine->stateTransition(addPlayerCommand2);"
            << "\n\tCommand* gameStartCommand = new Command(\"gamestart\");"
            << "\n\tengine->stateTransition(gameStartCommand);" << endl;
    
    Command* loadCommmand = new Command("loadmap MapTextFiles/UK.map");
    loadCommmand->Attach(observer);
    engine->stateTransition(loadCommmand);


    Command* validateCommand = new Command("validatemap");
    validateCommand->Attach(observer);
    engine->stateTransition(validateCommand); 
    
    
    Command* addPlayerCommand = new Command("addplayer Trump");
    addPlayerCommand->Attach(observer);
    engine->stateTransition(addPlayerCommand);

    Command* addPlayerCommand2 = new Command("addplayer Harris");
    addPlayerCommand2->Attach(observer);
    engine->stateTransition(addPlayerCommand2);
   
    Command* gameStartCommand = new Command("gamestart");
    gameStartCommand->Attach(observer);
    engine->stateTransition(gameStartCommand);
   
    
    //Example of observer notified when command is saved
    cout << "\nExample of the observer being notified when a command is saved\n----------------------------------------------" 
        << "\n\tCommand* command = new Command(\"loadmap MapTextFiles/UK.map\");"
        << "\n\tcommand->saveEffect(\"mapLoadedState\");"
        << endl;
    
    
    //Example of observer notified when command is save (saveEffect())
    Command* command = new Command("loadmap MapTextFiles/UK.map");
    command->Attach(observer);
    command->saveEffect("The map has been loaded");

    //Example of observer notified when commandProcessor saves a command
    //TODO: COMMAND PROCESSOR
    cout << "\nExample of the observer being notified when a command is saved by the command processor\n----------------------------------------------" 
        << "\n\tCommandProcessor* commandProcessor = new CommandProcessor();"
        << "\n\tcommandProcessor->saveCommand(command);"
        << endl;
    CommandProcessor* commandProcessor = new CommandProcessor();

    //player->DetachObservers(observer);
   // delete player;
    engine->Detach(observer);
    delete engine;
    delete observer;
    //delete orders; TODO: seg fault when deleting orders
}


// int main(){
//     testLoggingObserver();
//     return 0;
// }
