#include "../server/Server.hpp"
#include "CommandExecuter.hpp"


CommandExecuter::CommandExecuter() {}

CommandExecuter::~CommandExecuter() {
#pragma region FreeChannels
    std::map<std::string, ACommand*>::iterator it = _commands.begin();
    while (it != _commands.end())
    {
        delete (*it).second;
        it++;
    }
    _commands.clear();
#pragma endregion
}

bool CommandExecuter::executeCommand(const std::vector<std::string>& splitArgs,  std::pair<const int, NormalUser*>& user, std::map<int, NormalUser*> &_users, std::map<std::string, Channel*> &_channels, const std::string &pass) {
    std::map<std::string, ACommand*>::iterator it = _commands.find(Utility::toUpper(splitArgs[0]));
    std::cout << Utility::toUpper(splitArgs[0]);
    if (it != _commands.end()) {
        (*it).second->execute(splitArgs, user, _users, _channels, pass);
        return true;
    }
    else {
        std::cout << "Cannot find " << splitArgs[0] << " command!" << std::endl;
        return false;
    }
}

void CommandExecuter::addCommand(ACommand *Command) {
    _commands.insert(std::pair<std::string, ACommand*>(Command->getName(), Command));
}

void CommandExecuter::forgetCommand(ACommand *Command) {
    _commands.erase(Command->getName());
}

