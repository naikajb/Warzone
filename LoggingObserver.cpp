#include "LoggingObserver.h"
using namespace std;

Observer::~Observer(){
    delete this;
}

Observer::Observer(){
}

LogObserver::~LogObserver(){
    delete this;
}


// LogObserver constructor to create the log file
LogObserver::LogObserver(){
    logFileName = "gamelog.txt";
    logFile = std::ofstream(logFileName, std::ios::out);
    logFile << "Game Log\n---------------------------------------------" << std::endl;
    logFile.close();
}

void LogObserver::update(ILoggable* loggableObject){

}