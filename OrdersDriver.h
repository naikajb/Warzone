#ifndef ORDERSDRIVER_H
#define ORDERSDRIVER_H

#include <iostream>

// Forward declarations allow us to inform the compiler about the existence 
// of a class without including its full definition, preventing circular 
// dependencies and improving compilation efficiency.


class OrdersList;   //list of orders
class Order;        //base class for order types
class Deploy;       //derived class --> deploy order
class Advance;      //derived class --> advance order
class Bomb;         //derived class --> bomb order
class Blockade;     //derived class --> blockade order
class Airlift;      //derived class --> airlift order
class Negotiate;    //derived class --> negotiate order

// Function to test the OrdersList class and functionality
void testOrdersLists();

void testOrderExecution();

#endif // ORDERSDRIVER_H
