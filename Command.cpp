#include "Command.h"

Command::Command(const std::string& command) : cmd(command) {}

void Command::saveEffect(const std::string& effect) {
    this->effect = effect;
}