#include "LoggingObserver.h"


//Observer Class
Observer::~Observer(){
    //delete observer;
}

//Subject Class 

/*adds new observer to subject class list of observers*/
void Subject::Attach(Observer* observer){
    this->observer = observer;
}

void Subject::Notify(ILoggable* loggable){
    observer->update(*loggable);
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

void LogObserver::update(const ILoggable &loggable) const{
    logFile.open(logFileName, std::ios_base::app);
    
    if (!logFile.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return;
    }else{
        logFile << loggable.stringToLog() << std::endl;
        logFile.close();
    }
    
}

LogObserver::~LogObserver(){
    logFile.close();
}
