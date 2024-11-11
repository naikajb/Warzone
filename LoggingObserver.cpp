#include "LoggingObserver.h"
using namespace std;

//OBSERVER CLASS
Observer::~Observer(){
}

Observer::Observer(){
}

//LOGGINGOBSERVER CLASS
LogObserver::~LogObserver(){
    if (logFile.is_open()) {
        logFile.close();
    }
    
}

// LogObserver constructor to create the log file
LogObserver::LogObserver(){
    logFileName = "gamelog.txt";
    logFile = std::ofstream(logFileName, std::ios::out);
    logFile << "Game Log\n---------------------------------------------" << std::endl;
    logFile.close();
}

// LogObserver update method to write to the log file
void LogObserver::update(ILoggable* loggableObject){
    logFile.open(logFileName, std::ios::app);
    logFile << loggableObject->stringToLog() << std::endl;
    logFile.close();
}

//SUBJECT CLASS
// Subject::~Subject(){
//     Detach(observer);
//     observer = NULL;
// }
void Subject::Attach(Observer* observer){
    this->observer = observer;
}

void Subject::Detach(Observer* observer){
    observer = NULL;
}

void Subject::Notify(ILoggable* loggableObject){
    if (observer != NULL){
        observer->update(loggableObject);
    }
}

