#include "LoggingObserver.h"


//Subject Class 

/*adds new observer to subject class list of observers*/
void Subject::Attach(Observer* observer){
    this->observer = observer;
}

void Subject::Notify(ILoggable* loggable){
    observer->update(loggable);
}

void Subject::Detach(Observer* observer){
    delete observer;
}

Subject::~Subject(){
    delete observer;
}

//LogObserver Class
LogObserver::LogObserver(std::string logFilename){
    this->logFileName = logFilename;

    //clears the log file
    this->logFile.open(logFileName, std::ios::trunc);
    this->logFile.close();

}
LogObserver::LogObserver(){
    this->logFileName = "gamelog.txt";
}
void LogObserver::update(ILoggable* loggable){
    this->logFile.open(this->logFileName, std::ios_base::app);  
    this->logFile << loggable->stringToLog() << std::endl;
    this->logFile.close();
}

