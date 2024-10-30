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
    /** TestSubject* testSubject = new TestSubject();
     testSubject->Attach(observer);
     testSubject->Notify(testSubject);

     testSubject->setAction("New Action");*/

    GameEngine* engine = new GameEngine();
    CommandParser parser(engine);
    Order* order = new Deploy();
    //OrdersList* orderList = new OrdersList();
    Player* player = new Player("naika");
    player->AttachObserver(observer);
    
    cout << "GameEngine is created, its typeId is: " << typeid(engine).name() << endl;
    cout << "Order is created, its typeId is: " << typeid(*order).name() << endl;   
    //cout << "OrderList is created, its typeId is: " << typeid(orderList).name() << endl; 
    
    engine->Attach(observer);
    order->Attach(observer);
    //orderList->Attach(observer);
    parser.parseCommand("loadmap");
    string input;
    cout << "Enter a command: ";
    cin >> input;
    parser.parseCommand(input);
    cout << "Enter a command: ";
    cin >> input;
    parser.parseCommand(input);
    
    player->issueOrder(order);
    

    
    
}


int main(){
    testLoggingObserver();
    return 0;
}
