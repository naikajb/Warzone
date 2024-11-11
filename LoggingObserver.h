
#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>


class ILoggable{
    public: 
        virtual std::string stringToLog() = 0;
};
//saveCommand(), execute(), saveEffect(), addOrder(), transition() use the Notify() method
class Observer{
    public: 
        virtual ~Observer();
        virtual void update(ILoggable* loggableObject) = 0;
    protected:
        Observer();
}; 

class LogObserver: public Observer{
    public:
        LogObserver();
        ~LogObserver();
        void update(ILoggable* loggableObject);
    private: 
        std::ofstream logFile;
        std::string logFileName;
    
};

//classes Order, OrderList, GameEngine, Command and CommandProcessor are Subject and ILoggable objects
class Subject{
    public: 
        //~Subject();
        void Attach(Observer* observer);
        void Detach(Observer* observer);
        void Notify(ILoggable* loggableObject);
    private: 
        Observer* observer;
};

#endif