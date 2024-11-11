#ifndef FILE_COMMAND_PROCESSOR_ADAPTER_H
#define FILE_COMMAND_PROCESSOR_ADAPTER_H

#include "CommandProcessor.h"
#include "FileLineReader.h"

class FileCommandProcessorAdapter : public CommandProcessor {
private:
    FileLineReader *fileLineReader;

public:
    FileCommandProcessorAdapter(Observer*,FileLineReader* fileLine);
    ~FileCommandProcessorAdapter();
    Command* readCommand(std::string& commandstr) override;
    void saveCommand(Command* cmd) override;
    Command* getCommand(std::string& commandstr) override;
    bool validate(Command* cmd, const char* state) override;
};

#endif