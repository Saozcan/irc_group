#include "ACommand.hpp"

ACommand::ACommand() {}

ACommand::ACommand(const std::string &name) {
    _name = name;
}

ACommand::~ACommand() {}

void ACommand::setName(const std::string &name) {
    _name = name;
}

std::string ACommand::getName() {
    return _name;
}
