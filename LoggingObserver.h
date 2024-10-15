// 
#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

//saveCommand(), execute(), saveEffect(), addOrder(), transition() use the Notify() method
class Observer{
    public:
        void update(ILoggable* loggable);
        virtual ~Observer();
}; 

class LogObserver: public Observer{
    private: 
        std::string logFileName;
        std::ofstream logFile;
    public:
        LogObserver();
        LogObserver(std::string logFilename);
        void update(ILoggable* loggable);
        ~LogObserver();
};


//classes Order, OrderList, GameEngine, Command and CommandProcessor are Subject and ILoggable objects
class Subject{
    private: 
       Observer* observer;
    public:
        void Notify(ILoggable* loggable);
        void Attach(Observer* observer);
        void Detach(Observer* observer);
        virtual ~Subject();


};

class ILoggable{
    
    public:
        //the = 0 ensures that the method is pure virtual and must be implemented by the derived class 
        virtual std::string stringToLog() const = 0; 

};



#endif