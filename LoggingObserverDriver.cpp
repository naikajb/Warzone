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
    GameEngine* engine = new GameEngine();
    // CommandParser parser(engine);
    Deploy* order = new Deploy();
    Player* player = new Player("naika");
    OrdersList* orders = new OrdersList();
    
    orders->Attach(observer);
    orders->addOrder(order);
    //TODO: add the observer to the Command and CommandProcessor

    cout<< "\nAttaching observer to GameEngine, Order, and Player\n----------------------------------------------" 
        << "\n\texecuting engine->Attach(observer);"
        //<< "\n\texecuting order->Attach(observer);"
        << "\n\texecuting player->AttachObserver(observer);"
        << endl;
    engine->Attach(observer);
    //order->Attach(observer);
    // player->AttachObserver(observer);
   //TODO: add the observer to the Command and CommandProcessor 
    
    cout << "\nExample of the observer being notified when an order is added to the order list of a player\n----------------------------------------------" 
        << "\n\texecuting player->issueOrder(order);"
        << endl;
    //player->issueOrder();
    
    // cout << "\nExample of the observer being notified when an order is executed\n----------------------------------------------" 
    //     << "\n\texecuting order->executeOrder();"
    //     << "\n\tExecuting order->executeOrder();"
    //     << endl;
    // //order->executeOrder();

    cout << "\nExample of the observer being notified when the GameEngine changes its state\n----------------------------------------------" 
        << "\n\texecuting parser.parseCommand(\"loadmap\");"
        << "\n\texecuting parser.parseCommand(\"validatemap\");"
        << endl;
    // parser.parseCommand("loadmap");
    // parser.parseCommand("validatemap");
    string input;
    cout << "Enter a command: ";
    cin >> input;
    // parser.parseCommand(input);
    cout << "Enter a command: ";
    cin >> input;
    // parser.parseCommand(input);
    
    cout << "player address: " << player << endl;
    cout << "order address: " << order << endl;
    cout << "observer address: " << observer << endl;
    cout << "engine address: " << engine << endl;

    delete player;
    engine->Detach(observer);
    delete engine;
    delete observer;
    //delete orders; TODO: seg fault when deleting orders
}


// int main(){
//     testLoggingObserver();
//     return 0;
// }
