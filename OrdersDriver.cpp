#include "Orders.h"
#include "OrdersDriver.h"
#include "Player.h"
#include "GameEngine.h"

// Function to test the functuonality of the OrdersList class
// void testOrdersLists() {

//     // Create an instance of OrdersList to manage orders
//     OrdersList ordersList;

//     // Create different TYPES of orders
//     Order* deploy = new Deploy();
//     Order* advance = new Advance();
//     Order* bomb = new Bomb();
//     Order* blockade = new Blockade();
//     Order* airlift = new Airlift();
//     Order* negotiate = new Negotiate();

//     // Add created orders to the orders list
//     ordersList.addOrder(deploy);
//     ordersList.addOrder(advance);
//     ordersList.addOrder(bomb);
//     ordersList.addOrder(blockade);
//     ordersList.addOrder(airlift);
//     ordersList.addOrder(negotiate);

//     // Print the initial list of orders
//     std::cout << "Initial Orders List:" << std::endl;
//     std::cout << ordersList << std::endl;

//     // Move the 1rst order (deploy) to the end of the list
//     ordersList.move(0, 5);  // Move the first order to the end
//     std::cout << "After Moving Deploy to Last:" << std::endl;
//     std::cout << ordersList << std::endl;

//     // Remove an order from the orders list
//     ordersList.remove(2);  // Remove Bomb order
//     std::cout << "After Removing Bomb Order:" << std::endl;
//     std::cout << ordersList << std::endl;

//     // Execute the 'deploy' and the 'advance' orders to change their state
//     deploy->executeOrder();
//     advance->executeOrder();

//     // Print the orders list after executing 'deploy' order and 'advance' order
//     std::cout << "After Executing Deploy and Advance Orders:" << std::endl;
//     std::cout << ordersList << std::endl;
// }

void testOrderExecution()
{

    clearPlayerList();
    Observer *ob = new LogObserver();

    Player *p1 = new Player(ob, "Jake");
    Player *p2 = new Player(ob, "Joop");
    Player *p3 = new Player(ob, "Tanya");

    addToPlayerList(p1);
    addToPlayerList(p2);
    addToPlayerList(p3);

    Territory *t1 = new Territory("1", new Continent("C", 0));
    Territory *t2 = new Territory("2", new Continent("C", 0));
    Territory *t3 = new Territory("3", new Continent("C", 0));
    Territory *t4 = new Territory("4", new Continent("C", 0));
    Territory *t5 = new Territory("5", new Continent("C", 0));
    Territory *t6 = new Territory("6", new Continent("C", 0));

    t1->addAdjTerritories(t2);
    t2->addAdjTerritories(t1);

    t1->addAdjTerritories(t3);
    t3->addAdjTerritories(t1);

    t2->addAdjTerritories(t4);
    t4->addAdjTerritories(t2);

    t3->addAdjTerritories(t4);
    t4->addAdjTerritories(t3);

    t3->addAdjTerritories(t5);
    t5->addAdjTerritories(t3);

    t4->addAdjTerritories(t6);
    t6->addAdjTerritories(t6);

    t5->addAdjTerritories(t6);
    t6->addAdjTerritories(t5);

    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p1->addTerritory(t6);

    p2->addTerritory(t3);
    p2->addTerritory(t5);

    p3->addTerritory(t4);

    // Deploy Test Works

    cout << "Deploy Order Test" << endl
         << endl;

    Order *deployTest = new Deploy(ob, p1, 4, t1);

    deployTest->Attach(ob);

    deployTest->execute();

    cout << endl
         << endl;

    // Advance Test Works -> Tried everything

    cout << "Advance Order Test (Battle)" << endl
         << endl;

    t1->setNumArmies(10);
    t2->setNumArmies(2);
    t3->setNumArmies(3);

    Order *advanceTest = new Advance(ob, p1, 6, t1, t3);

    advanceTest->Attach(ob);

    advanceTest->execute();

    cout << endl
         << endl;

    cout << "Advance Order Test (Friendly)" << endl
         << endl;

    t1->setNumArmies(10);
    t2->setNumArmies(2);
    t3->setNumArmies(3);

    Order *advanceTest2 = new Advance(ob, p1, 6, t1, t2);

    advanceTest2->Attach(ob);

    advanceTest2->execute();

    cout << endl
         << endl;

    // Airlift Test Works

    cout << "Airlift Order Test" << endl
         << endl;

    t1->setNumArmies(12);
    t6->setNumArmies(2);

    Order *airliftTest = new Airlift(ob, p1, 12, t1, t6);

    airliftTest->Attach(ob);

    airliftTest->execute();

    cout << endl
         << endl;

    // Bomb Test Works

    cout << "Bomb Order Test" << endl
         << endl;

    t5->setNumArmies(10);

    Order *bombTest = new Bomb(ob, p3, t1);

    bombTest->Attach(ob);

    bombTest->execute();

    cout << endl
         << endl;

    // Blockade Test Works

    cout << "Blockade Order Test" << endl
         << endl;

    Order *blockadeTest = new Blockade(ob, p1, t6);

    blockadeTest->Attach(ob);

    blockadeTest->execute();

    cout << endl
         << endl;

    // Negotiate Test Works

    cout << "Negotiate Order Test" << endl
         << endl;

    Order *o = new Negotiate(ob, p1, p2);
    o->Attach(ob);
    Order *o2 = new Negotiate(ob, p1, p3);
    o2->Attach(ob);

    o->execute();
    o2->execute();

    Order *boomboom = new Bomb(ob, p3, t2);

    boomboom->Attach(ob);

    boomboom->execute();

    cout << "Negotiation pair reset." << endl;

    resetNegotiatePairs();

    boomboom->execute();

    clearPlayerList();
}

// Main function to run the test
int main_OrdersDriver()
{
    testOrderExecution();
    return 0;
}
