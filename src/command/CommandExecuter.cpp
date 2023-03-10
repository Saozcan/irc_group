#include "CommandExecuter.hpp"

CommandExecuter::CommandExecuter() {}

CommandExecuter::~CommandExecuter() {
//#pragma region FreeChannels
    std::map<std::string, ACommand*>::iterator it = _commands.begin();
    while (it != _commands.end())
    {
        delete (*it).second;
        it++;
    }
    _commands.clear();
//#pragma endregion
}

void CommandExecuter::executeCommand(std::string command) {
    std::map<std::string, ACommand*>::iterator it = _commands.find(command);

    if (it != _commands.end())
        (*it).second->execute();
    else
        std::cout << "Cannot find " << command << " command!" << std::endl;
}

void CommandExecuter::addCommand(ACommand *Command) {
    _commands.insert(std::make_pair(Command->getName(), Command));
}

void CommandExecuter::forgetCommand(ACommand *Command) {
    _commands.erase(Command->getName());
}